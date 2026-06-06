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

## Explanation

正确答案是 A、B、D。CTAD 会根据构造实参推导类模板实参，省去显式写模板参数。 A 正确：｀std::pair p{1, 2.0};｀（推导为 ｀std::pair<int, double>｀）；B 正确：｀std::vector v{1, 2, 3};｀（推导为 ｀std::vector<int>｀）；C 错误：｀std::pair<> p{1, 2.0};｀（空括号不是 CTAD 语法，编译错误）；D 正确：｀std::tuple t{true, 'a', 3.14f};｀（推导为 ｀std::tuple<bool, char, float>｀）。常见误区是只记住术语名称，而忽略每个选项中的限定条件、生命周期、同步关系或复杂度前提。
