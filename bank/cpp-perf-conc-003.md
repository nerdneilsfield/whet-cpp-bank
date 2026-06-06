---
qid: cpp-perf-conc-003
type: single
kp: [cpp-concurrency, cpp-memory-mgmt]
primary_kp: cpp-concurrency
difficulty: hard
answer_key: A
tags: [performance, code-taste]
---

要在多线程程序里给每个线程一个 4 KB 的"暂存缓冲"（scratch buffer），调用频繁但每次调用只是读写自己线程的那块。下面四种实现功能等价，哪个最值得采用？

```cpp
// A
char* get_scratch() {
    thread_local char buf[4096];
    return buf;
}

// B
static std::unordered_map<std::thread::id, std::unique_ptr<char[]>> pool;
static std::mutex m;
char* get_scratch() {
    auto id = std::this_thread::get_id();
    std::lock_guard lk(m);
    auto it = pool.find(id);
    if (it == pool.end()) {
        auto [it2, _] = pool.emplace(id, std::make_unique<char[]>(4096));
        return it2->second.get();
    }
    return it->second.get();
}

// C
char* get_scratch() {
    return new char[4096];  // 调用者负责 delete
}

// D
static char shared_buf[4096];
static std::mutex m;
template<class F>
auto with_scratch(F&& f) {
    std::lock_guard lk(m);
    return f(shared_buf);
}
```

A. A — thread_local 数组，每线程一份
B. B — 全局 map 按 thread id 存，按需创建
C. C — 每次调用 new 一块 4KB
D. D — 全局共享一块，用 mutex 序列化访问

---

**解析：**

选 A。这道题考的是"thread-local 存储 vs 锁保护映射 vs 每次分配"——访问代价天差地别。

逐一品味：

- **A**：`thread_local` 让编译器/链接器在每个线程的 TLS 段里分配 4 KB。访问 `buf` 是一条指令（GCC `mov %fs:offset, %rax` 或类似），**几乎和访问普通局部变量一样快** (~1 cycle)。无锁、无堆分配、无 map 查找。每个线程独立的内存，零 false sharing。**正确做法**。
- **B**：每次调用 ① 取 thread::id（一次系统/库函数调用 ~10 ns）；② 上锁（无竞争 ~10 ns，有竞争从 100 ns 到无穷）；③ map 查找（hash + 比较 ~50 ns）；④ 解锁。16 线程都在这把锁上排队，本来想避免共享反而**用锁把所有线程串行化**，吞吐崩溃。比 A 慢 **100–1000 倍**。
- **C**：每次调用 `new char[4096]`——一次 malloc 系统库调用（~50–200 ns 无竞争，多线程下 allocator 有内部锁），加上**调用方必须记得 free**（漏 free 就泄露）。1e6 次调用就是 100 ms 的分配/释放开销 + 内存碎片化。比 A 慢 **100 倍**且不安全。
- **D**：所有线程争一把 mutex，**完全串行化**——16 线程在 4 KB 上排队，等同于单线程。比 A 慢 = 线程数倍（如 16×）。完全失去并行性。

A 的关键是 TLS 把"每线程一份数据"从概念变成硬件能直接寻址的事——`fs:`/`gs:` 段寄存器加 offset 即得，访问开销和栈/全局变量同级。

**核心识别点：**
- 看见"每线程一份数据"用 map+mutex 实现 → 警觉 `thread_local` 是为这场景生的
- 看见循环里 `new` + `delete` 一块小内存 → 警觉是不是该改 thread_local 复用
- 看见全局 buffer + mutex 把多线程串行化 → 警觉这是错把"共享"当目的而非手段
- `thread_local` 的访问 ~1 cycle，mutex 无竞争 ~10 ns，malloc ~100 ns——三个数量级
- POD/数组用 `thread_local`：构造析构是 zero-cost；类型有非平凡构造时才有 TLS 初始化开销

**来源：** Anthony Williams, "C++ Concurrency in Action" 2nd ed., §4.3 "thread_local variables"；ELF TLS ABI 文档；Intel Optimization Reference Manual, §11.6 "Thread-Local Storage Access".

## Explanation

正确答案应让生产者和消费者少阻塞、少忙等，并保证等待条件写对。条件变量适合低频等待，忙等适合极短临界等待；无界自旋会浪费核心并拖慢系统。常见误区是把“无锁”当作必然更快，忽略缓存一致性流量和退避策略。
