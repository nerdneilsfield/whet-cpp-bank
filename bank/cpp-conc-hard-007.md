---
qid: cpp-conc-hard-007
type: single
kp: [cpp-concurrency]
difficulty: medium
answer_key: D
---

以下用 CAS 实现的自旋锁代码：

```cpp
class SpinLock {
    std::atomic<bool> locked{false};
public:
    void lock() {
        bool expected = false;
        while (!locked.compare_exchange_weak(expected, true,
                   std::memory_order_acquire,
                   std::memory_order_relaxed)) {
            expected = false;  // (X)
        }
    }
    void unlock() {
        locked.store(false, std::memory_order_release);
    }
};
```

关于 `(X)` 处 `expected = false` 的作用，以下说法**正确**的是？

A. 仅用于处理 `compare_exchange_weak` 的伪失败；真正的竞争失败时 `expected` 已经是 `false`，不需要重置
B. 没有实际意义，删除也不影响正确性，因为 `locked` 只会是 `true` 或 `false`
C. 防止编译器将循环优化为死循环
D. `compare_exchange_weak` 失败时会将 `expected` 更新为 `locked` 的当前值（即 `true`），不重置则下一次循环条件永远不匹配，导致死循环

## Explanation

正确答案是 D。`memory_order_relaxed` 只保证原子性，不提供跨线程同步顺序。选项 D 的表述“｀compare_exchange_weak｀ 失败时会将 ｀expected｀ 更新为 ｀locked｀ 的当前值（即 ｀true｀），不重置则下一次循环条件永远不匹配，导致死循环”正好符合该规则。A、B、C 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
