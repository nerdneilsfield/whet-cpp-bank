---
qid: cpp-mem-fill-med-001
type: fill
kp: [cpp-memory-mgmt]
difficulty: medium
answer_key: "std::make_unique"
---
C++14 引入用 ___ 创建 `unique_ptr`。

---

**解析：**

`std::make_unique<T>(args...)` 是 C++14 新增的工具函数，它以类型安全且异常安全的方式构造 `T` 对象并返回 `std::unique_ptr<T>`。相比直接使用 `new`，它能避免因参数求值顺序导致的潜在内存泄漏，且代码更简洁。`std::make_shared` 则有 C++11 版本。

## Explanation

答案是 `std::make_unique`，它是 C++14 提供的推荐工厂函数，用于创建并返回 `std::unique_ptr<T>`。它把对象构造和智能指针接管合成一个表达式，减少裸 `new` 暴露。不要与 `std::make_shared` 混淆，后者创建的是共享所有权的 `shared_ptr`。
