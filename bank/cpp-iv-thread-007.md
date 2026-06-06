---
qid: cpp-iv-thread-007
type: short
kp: [cpp-interview]
difficulty: hard
tags: [华为, 腾讯]
rubric:
  - 准确说出 volatile 的语义（禁止编译器优化，不保证原子性和内存序）
  - 准确说出 atomic 的语义（原子性 + 内存序保证）
  - 能举出 volatile 在多线程中失效的具体例子
  - 知道 volatile 的合法用场（MMIO、longjmp、信号处理）
  - 能解释为何 volatile 不能替代 atomic（硬件层面 + 编译器层面）
---

# `volatile` 和 `atomic` 的区别？为什么多线程中不能用 `volatile` 代替 `atomic`？

## 参考答案

### volatile 的实际语义

`volatile` 告诉编译器：**每次读写都必须真正访问内存，不允许缓存到寄存器或重排此访问**。

```cpp
volatile int reg = 0;
// 每次 read/write 都生成 load/store 指令，不被优化掉
while (reg == 0) { }   // 编译器不会优化为 while(true)
```

`volatile` **不**提供：
- 原子性（read-modify-write 仍非原子）
- 内存顺序保证（不阻止 CPU 乱序执行）
- 跨线程可见性（不插入内存屏障）

---

### atomic 的实际语义

`std::atomic<T>` 提供三重保证：

| 保证 | 机制 |
|------|------|
| **原子性** | 单次 read/write/RMW 不可分割（lock-free 或 mutex） |
| **可见性** | store 后对所有线程可见（内存屏障/fence） |
| **内存序** | 可指定操作间的 happens-before 关系 |

---

### 为什么 volatile 在多线程中不够用

**问题1：非原子的 read-modify-write**

```cpp
volatile int counter = 0;

void increment() {
    counter++;   // 编译为: load → inc → store（三条指令）
}

// 两线程同时 counter++（初始值=0）：
// T1: load(0)
// T2: load(0)       ← T1 的 store 还没执行
// T1: store(1)
// T2: store(1)      ← T1 的结果被覆盖！
// 结果：counter=1，期望=2
```

**问题2：CPU 乱序执行（volatile 无法阻止）**

```cpp
volatile bool ready = false;
volatile int data = 0;

// 生产者（核0）
data = 42;
ready = true;   // volatile 保证写入内存，但 CPU 可能乱序：ready 先写

// 消费者（核1）
while (!ready) {}
use(data);   // 可能看到 ready=true 但 data=0（x86 较少见，ARM/Power 常见）
```

`std::atomic` 的 release/acquire 会插入**内存屏障（memory barrier/fence）**，强制 CPU 完成屏障前的所有写操作。

**问题3：编译器重排**

```cpp
// 编译器可将 data 的写移到 ready 的写之后（volatile 不禁止跨变量重排）
// atomic 的 memory_order_release 明确禁止 store 上移
```

---

### 正确做法对比

```cpp
// ❌ 错误：volatile 无法保证线程安全
volatile int flag = 0;
flag++;   // 数据竞争 + 非原子

// ✅ 正确：atomic 保证原子性和内存序
std::atomic<int> flag{0};
flag.fetch_add(1, std::memory_order_relaxed);  // 原子 RMW

// ✅ 正确：发布-订阅模式
std::atomic<bool> ready{false};
int data = 0;

// 生产者
data = 42;
ready.store(true, std::memory_order_release);  // 屏障：data 写先于 ready 写

// 消费者
while (!ready.load(std::memory_order_acquire)) {}  // 屏障：ready 读先于 data 读
assert(data == 42);  // 保证成立
```

---

### volatile 的合法使用场景

| 场景 | 原因 |
|------|------|
| 内存映射 I/O（MMIO） | 硬件寄存器映射到内存，每次读写都有副作用 |
| `setjmp`/`longjmp` | 防止变量被优化掉导致值丢失 |
| 信号处理函数中的全局标志 | `sig_atomic_t volatile`（POSIX 规定） |
| 调试时防止变量被优化消除 | 临时使用 |

---

### 面试一句话总结

> `volatile` 禁止编译器缓存和重排，但不保证原子性和 CPU 内存序；`atomic` 三者都保证。多线程共享变量必须用 `atomic` 或 `mutex`，`volatile` 无法替代，用它会产生数据竞争（UB）。
