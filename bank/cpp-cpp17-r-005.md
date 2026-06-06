---
qid: cpp-cpp17-r-005
type: single
kp: [cpp-cpp14-17]
difficulty: easy
answer_key: "B"
---

### 题目

阅读以下代码，`p` 的推导类型是什么，程序输出是什么？

```cpp
#include <iostream>
#include <utility>
#include <type_traits>

int main() {
    auto p = std::pair{1, 2.0};   // CTAD
    std::cout << std::is_same_v<decltype(p), std::pair<int, double>>;
    std::cout << " ";
    std::cout << p.first << " " << p.second;
}
```

A. 编译错误：`std::pair` 需要显式模板参数
B. 输出 `1 1 2`（第一个 `1` 是 `true`）
C. 输出 `0 1 2`
D. `p` 类型为 `std::pair<int, int>`，输出 `1 1 2`

## Explanation

C++17 类模板实参推导（CTAD）允许 `std::pair{1, 2.0}` 自动推导为 `std::pair<int, double>`，不需要 `std::make_pair` 或显式模板参数。`std::is_same_v<decltype(p), std::pair<int, double>>` 为 `true`（输出 `1`）。`p.first = 1`，`p.second = 2`（`double` 输出无小数部分时显示 `2`）。完整输出：`1 1 2`。
