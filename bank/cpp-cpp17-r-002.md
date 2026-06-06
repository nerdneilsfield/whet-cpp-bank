---
qid: cpp-cpp17-r-002
type: single
kp: [cpp-cpp14-17]
difficulty: easy
answer_key: "C"
---

### 题目

阅读以下代码，程序运行时发生什么？

```cpp
#include <iostream>
#include <optional>
#include <stdexcept>

std::optional<int> get_value(bool has) {
    if (has) return 42;
    return std::nullopt;
}

int main() {
    auto v = get_value(false);
    std::cout << v.value();   // 行 A
}
```

A. 输出 `0`（默认值）
B. 输出未定义的垃圾值
C. 抛出 `std::bad_optional_access` 异常
D. 编译错误：`optional` 没有 `value()` 成员

## Explanation

`std::optional::value()` 在对象不含值时抛出 `std::bad_optional_access`（继承自 `std::exception`）。这与 `operator*` 不同——`*v` 在无值时是未定义行为，而 `v.value()` 提供有检查的访问。程序抛出异常并终止（若未捕获）。
