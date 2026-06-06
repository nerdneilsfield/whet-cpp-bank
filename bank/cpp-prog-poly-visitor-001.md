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

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <variant>
#include <string>

using Value = std::variant<int, double, std::string>;

std::string describe(const Value& v);
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数