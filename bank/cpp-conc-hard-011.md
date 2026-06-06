---
qid: cpp-conc-hard-011
type: single
kp: [cpp-concurrency]
difficulty: hard
answer_key: B
---

C++20 引入了 `std::atomic<std::shared_ptr<T>>`。以下代码在 C++17 中存在数据竞争：

```cpp
// C++17 — 有问题
std::shared_ptr<Widget> g_ptr = std::make_shared<Widget>(1);

// 线程1（读者）
auto local = g_ptr;  // 拷贝引用计数 — 非原子！

// 线程2（写者）
g_ptr = std::make_shared<Widget>(2);  // 修改引用计数 — 非原子！
```

C++20 `std::atomic<std::shared_ptr<T>>` 解决了什么核心问题？

A. 防止 `Widget` 对象本身被并发访问——对象内部的成员变量访问变为线程安全
B. 使 `shared_ptr` 的**控制块指针替换**（即 `g_ptr` 本身的赋值/拷贝）成为原子操作，消除读写 `shared_ptr` 对象时的数据竞争；`Widget` 内部成员的线程安全仍需另行保证
C. 用硬件 CAS 替换 `shared_ptr` 内部的引用计数自增，提升多线程下的性能
D. 等价于在所有 `shared_ptr` 操作外加 `std::mutex`，语义上无区别，只是语法更简洁

## Explanation

正确答案是 B。`auto` 按模板实参推导规则工作，常会丢弃顶层 `const` 和引用，除非显式写成 `auto&`。选项 B 的表述“使 ｀shared_ptr｀ 的**控制块指针替换**（即 ｀g_ptr｀ 本身的赋值/拷贝）成为原子操作，消除读写 ｀shared_ptr｀ 对象时的数据竞争；｀Widget｀ 内部成员的线程安全仍需另行保证”正好符合该规则。A、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
