---
qid: cpp-cpp17-003
type: single
kp: [cpp-cpp14-17]
difficulty: easy
answer_key: A
---

# 认知：std::optional 的含义

`std::optional<int>` 表示什么？

A. 一个可能持有 `int` 值、也可能为空（`nullopt`）的对象
B. 一个指向 `int` 的可空指针
C. 一个只读的 `int` 包装器
D. 一个线程安全的 `int` 容器

## 解析

正确答案是 A。`std::optional<T>` 表示可能有值也可能为空，访问前应检查是否持有值。选项 A 的表述“一个可能持有 ｀int｀ 值、也可能为空（｀nullopt｀）的对象”正好符合该规则。B、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
