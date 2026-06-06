---
qid: cpp-iv-thread-002
type: short
kp: [cpp-interview]
difficulty: medium
tags: [腾讯, Google]
rubric:
  - 能说出 mutex 和 atomic 的核心区别（锁 vs 无锁指令）
  - 知道 atomic 适用于单个变量的简单读写/RMW，mutex 适用于复合操作或多变量
  - 了解 memory_order 语义（relaxed/acquire-release/seq_cst）
  - 清楚 atomic 的硬件开销（lock-free 不等于零开销）
  - 能举出典型场景：计数器用 atomic，临界区用 mutex
---

# `std::mutex` vs `std::atomic` 的选择原则？原子操作的开销？

## 参考答案

### 核心区别

| 维度 | `std::mutex` | `std::atomic<T>` |
|------|-------------|-----------------|
| 实现机制 | 系统调用（futex）+ 内核仲裁 | CPU 原子指令（LOCK XCHG / CMPXCHG） |
| 适用对象 | 任意复合操作、多变量不变式 | 单一变量的读/写/RMW |
| 线程阻塞 | 会（竞争时 sleep） | 不会（自旋或直接成功） |
| 内存序控制 | 隐式 seq_cst（全序） | 可显式指定（relaxed → seq_cst） |
| 可重入 | 需 `recursive_mutex` | 不适用 |

---

### 选择原则

**用 `std::atomic` 当：**
- 操作对象是**单个标量**（int、bool、指针）
- 操作是**单步** read / write / fetch_add / compare_exchange
- 追求最低延迟（热路径计数器、标志位、引用计数）

```cpp
std::atomic<int> counter{0};
counter.fetch_add(1, std::memory_order_relaxed);  // 最低开销

std::atomic<bool> ready{false};
// 生产者
ready.store(true, std::memory_order_release);
// 消费者
while (!ready.load(std::memory_order_acquire)) { /* spin */ }
```

**用 `std::mutex` 当：**
- 保护**多个变量**的一致性（如链表节点 + 长度）
- 操作不是单步（如 read-modify-write 跨两个不同变量）
- 需要 **条件等待**（与 `condition_variable` 搭配）

```cpp
std::mutex mtx;
std::vector<int> buf;
int size = 0;

void push(int v) {
    std::lock_guard lk(mtx);
    buf.push_back(v);  // buf 和 size 必须同时更新
    ++size;
}
```

---

### 原子操作的硬件开销

原子操作**并非免费**，常见误解是"lock-free = 零开销"：

1. **LOCK 前缀指令**（x86）：锁总线或锁 Cache Line，延迟约 10–50 ns（vs 普通指令 < 1 ns）
2. **Cache line invalidation**：修改原子变量会使其他核心的 L1/L2 缓存失效，高争用时触发 **False Sharing**
3. **内存屏障**：`seq_cst` 会插入 `MFENCE`，强制全局可见性，代价高于 `relaxed`

```cpp
// 性能递增（开销递减）
std::memory_order_seq_cst  // 默认，最强，最慢
std::memory_order_acq_rel  // 用于 RMW（fetch_add 等）
std::memory_order_release  // store
std::memory_order_acquire  // load
std::memory_order_relaxed  // 只保原子性，无顺序保证（计数器场景）
```

**基准参考（x86，单核争用）：**

| 操作 | 大约延迟 |
|------|---------|
| 普通 load/store | < 1 ns |
| atomic load (relaxed) | ~1 ns |
| atomic fetch_add (seq_cst) | ~10–30 ns |
| mutex lock/unlock（无争用） | ~20–50 ns |
| mutex lock/unlock（有争用） | ~100–1000 ns |

---

### 面试一句话总结

> 单变量单步操作用 `atomic`，多变量或复合操作用 `mutex`；`atomic` 不是零开销，高争用时 false sharing 可比 mutex 更慢。
