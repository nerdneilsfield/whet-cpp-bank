---
qid: cpp-prog-poly-visitor-001
type: prog
kp: [cpp-polymorphism]
primary_kp: cpp-polymorphism
difficulty: hard
toolchain: [make]
tests_dir: tests/cpp-prog-poly-visitor-001/
---
使用 std::variant<int, double, std::string> 与 std::visit 实现 describe(v)：int 返回 "int:N"，double 返回 "double:N"（用 std::to_string），string 返回 "str:S"。

### 函数签名
```cpp
// solution.hpp
#pragma once
#include <variant>
#include <string>

using Value = std::variant<int, double, std::string>;

std::string describe(const Value& v);
```

### 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## Explanation
`std::visit` 需要一个能处理三种备选类型的 visitor，可以用重载 lambda 或泛型 lambda 加 `if constexpr`。`int` 拼接 `"int:" + std::to_string(x)`，`double` 用 `std::to_string` 保持题目要求的格式，`std::string` 拼接 `"str:"`。注意 visitor 返回类型应统一为 `std::string`。
