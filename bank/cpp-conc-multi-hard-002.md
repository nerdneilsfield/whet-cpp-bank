---
qid: cpp-conc-multi-hard-002
type: multi
kp: [cpp-concurrency]
difficulty: hard
answer_key: [A, B, D]
---
关于 `std::atomic` 的操作特性，以下说法正确的是哪些？

```cpp
std::atomic<int> a;
int expected = 0;
while (!a.compare_exchange_weak(expected, expected + 1)) { /* retry */ }
```

A. `std::atomic<T>::is_lock_free()` 可能在运行期返回 false——某些类型（如较大的结构体）不能用 CPU 原子指令完成，会退化为内部锁实现。
B. `compare_exchange_weak` 允许"伪失败"（spurious failure），即使 expected 与当前值相等也可能失败返回，因此通常配合循环使用；`compare_exchange_strong` 不允许伪失败。
C. `compare_exchange_weak/strong` 完全免疫 ABA 问题，因为它们比较的是值与内存地址的组合。
D. `compare_exchange_*` 失败时会把当前实际值写回 `expected` 参数，便于循环时重新计算下一个候选值。

---

**解析：**

A 正确：`is_lock_free` 对某些大小或对齐不利的类型可能在运行期为 false，标准库会改用内部互斥锁实现 atomic 接口，此时所谓"原子"操作其实是加锁的。`is_always_lock_free`（C++17，constexpr）才是编译期保证。
B 正确：weak 版本可能因 LL/SC 实现等微架构原因 spurious 失败，要在循环里使用；strong 版本由库内部循环消除 spurious 失败但单次开销更大。在循环中用 weak 通常性能更好。
C 错误：CAS 仅比较"值是否相等"，对 ABA 完全不免疫——值从 A 变到 B 再变回 A，CAS 看到的依然相等。解决 ABA 通常需要带版本号的 CAS（如 `atomic<pair<T*, uint64_t>>` 或硬件 DCAS）。
D 正确：CAS 失败时把当前真实值写入 expected，是 C++ 原子接口的关键设计——便于下一轮循环用最新值重新计算并尝试。