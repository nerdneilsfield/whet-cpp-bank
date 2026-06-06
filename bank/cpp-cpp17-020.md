---
qid: cpp-cpp17-020
type: multi
kp: [cpp-cpp14-17]
difficulty: easy
answer_key: [B, C]
---

# 代码阅读：C++14/17 特性综合判断

下列代码片段中，哪些能在 C++17 下正确编译并按预期工作？（多选）

```cpp
// 片段 A
std::pair p = {1, "hello"};       // CTAD 推导 pair<int, const char*>
auto [x, y] = p;
std::cout << y.size();            // const char* 没有 .size()

// 片段 B
auto square = [](auto x) { return x * x; };
std::cout << square(3) << " " << square(2.5);

// 片段 C
template<typename T>
constexpr T e = T(2.71828182845904523536);
double euler = e<double>;

// 片段 D
[[nodiscard]] int compute() { return 42; }
int main() { compute(); }         // 忽略返回值
```

A. 片段 A：能正确编译并输出字符串长度
B. 片段 B：泛型 lambda，`square(3)` 输出 `9`，`square(2.5)` 输出 `6.25`
C. 片段 C：C++14 变量模板，`euler` 值为约 `2.71828`
D. 片段 D：忽略 `[[nodiscard]]` 返回值不影响编译，只产生警告（而非错误）
