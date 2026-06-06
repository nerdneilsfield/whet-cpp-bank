---
qid: cpp-conc-hard-010
type: single
kp: [cpp-concurrency]
difficulty: hard
answer_key: A
---

`std::atomic_thread_fence` 是独立于原子操作的内存栅栏。分析以下代码：

```cpp
std::atomic<int> flag{0};
int data = 0;

// 线程1
data = 100;                                                    // (A)
std::atomic_thread_fence(std::memory_order_release);           // (B)
flag.store(1, std::memory_order_relaxed);                      // (C)

// 线程2
while (flag.load(std::memory_order_relaxed) != 1) {}           // (D)
std::atomic_thread_fence(std::memory_order_acquire);           // (E)
assert(data == 100);                                           // (F)
```

关于此代码是否正确同步，以下说法**正确**的是？

A. 正确同步。`release` 栅栏 + `relaxed` store，配合 `relaxed` load + `acquire` 栅栏，等效于 `release` store + `acquire` load，断言不会触发
B. 不正确。独立栅栏不能替代原子操作上的内存序；必须在 `store`/`load` 上使用 `release`/`acquire`
C. 不正确。`(B)` 的 `release` 栅栏必须紧贴 `(C)` 的 store 之后，否则不起作用
D. 正确，但仅限 x86 平台；在 ARM 上 `relaxed` load 不足以触发同步

## Explanation

正确答案是 A。`memory_order_relaxed` 只保证原子性，不提供跨线程同步顺序。选项 A 的表述“正确同步。｀release｀ 栅栏 + ｀relaxed｀ store，配合 ｀relaxed｀ load + ｀acquire｀ 栅栏，等效于 ｀release｀ store + ｀acquire｀ load，断言不会触发”正好符合该规则。B、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
