---
qid: cpp-move-019
type: multi
kp: [cpp-move-semantics]
difficulty: easy
answer_key: [A, C, D]
---

# 关于 std::move 的正确说法

以下关于 `std::move` 的描述，哪些是正确的？（多选）

A. `std::move` 本身不移动任何数据，只是一次类型转换
B. 对 `const` 对象调用 `std::move` 后一定会调用移动构造函数
C. `std::move` 将 lvalue 转换为 xvalue（将亡值），属于 rvalue
D. 对某个变量调用 `std::move` 后，该变量仍可以被销毁和重新赋值
E. `std::move` 会立即释放被移动对象的内存

## 解析

正确答案是 A、C、D。`std::move` 只是转换值类别，把左值转为 xvalue；实际移动取决于后续重载。对 `const` 对象 `std::move` 得到的是 `const T&&`，通常无法调用需要修改源对象的移动构造，所以 B 错；E 错在它不会释放内存。
