---
qid: cpp-cpp17-007
type: multi
kp: [cpp-cpp14-17]
difficulty: easy
answer_key: [A, C]
---

# 认知：std::make_unique 的优势

C++14 引入 `std::make_unique<T>(args...)` 相比直接 `new`，有哪些优势？（多选）

A. 异常安全：避免裸 `new` 在多参数函数中因求值顺序导致的内存泄漏
B. 性能更高：`make_unique` 使用了内存池优化
C. 代码简洁：无需重复写类型名，如 `auto p = std::make_unique<Foo>(args)` 而非 `std::unique_ptr<Foo> p(new Foo(args))`
D. 支持自定义删除器，而 `new` 不支持

## 解析

正确答案是 A、C。`auto` 按模板实参推导规则工作，常会丢弃顶层 `const` 和引用，除非显式写成 `auto&`。 A 正确：异常安全：避免裸 ｀new｀ 在多参数函数中因求值顺序导致的内存泄漏；B 错误：性能更高：｀make_unique｀ 使用了内存池优化；C 正确：代码简洁：无需重复写类型名，如 ｀auto p = std::make_unique<Foo>(args)｀ 而非 ｀std::unique_ptr<Foo> p(new Foo(args))｀；D 错误：支持自定义删除器，而 ｀new｀ 不支持。常见误区是只记住术语名称，而忽略每个选项中的限定条件、生命周期、同步关系或复杂度前提。
