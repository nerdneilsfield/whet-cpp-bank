---
qid: cpp-cpp17-008
type: multi
kp: [cpp-cpp14-17]
difficulty: easy
answer_key: [A, B, D]
---

# 认知：C++17 CTAD 适用场景

下列哪些写法能在 C++17 中利用 CTAD 省略模板参数？（多选）

A. `std::pair p{1, 2.0};`（推导为 `std::pair<int, double>`）
B. `std::vector v{1, 2, 3};`（推导为 `std::vector<int>`）
C. `std::pair<> p{1, 2.0};`（空括号不是 CTAD 语法，编译错误）
D. `std::tuple t{true, 'a', 3.14f};`（推导为 `std::tuple<bool, char, float>`）
