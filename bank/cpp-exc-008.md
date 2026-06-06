---
qid: cpp-exc-008
type: multi
kp: [cpp-exceptions]
difficulty: easy
answer_key: [A, C, D]
---

# C++ 异常处理：可以抛出的类型

C++ 中 `throw` 可以抛出哪些类型？（多选）

A. `int`
B. 函数指针（抛出本身不会报错，但极少用）
C. `std::string`
D. 自定义类对象
E. `void`（不能抛出 void 类型）

## 解析

正确答案是 A、C、D。`throw` 表达式用于抛出异常；在 `catch` 中单独写 `throw;` 表示重新抛出当前异常。 A 正确：｀int｀；B 错误：函数指针（抛出本身不会报错，但极少用）；C 正确：｀std::string｀；D 正确：自定义类对象；E 错误：｀void｀（不能抛出 void 类型）。常见误区是只记住术语名称，而忽略每个选项中的限定条件、生命周期、同步关系或复杂度前提。
