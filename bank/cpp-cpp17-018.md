---
qid: cpp-cpp17-018
type: single
kp: [cpp-cpp14-17]
difficulty: easy
answer_key: D
---

# 代码阅读：std::variant 访问错误类型

```cpp
#include <variant>
#include <iostream>

int main() {
    std::variant<int, std::string> v = 42;
    std::cout << std::get<std::string>(v) << "\n";
}
```

程序运行时会发生什么？

A. 输出 `42`（自动类型转换）
B. 输出空字符串
C. 编译错误：`std::get` 类型不匹配
D. 抛出 `std::bad_variant_access` 异常

## Explanation

正确答案是 D。`std::variant` 在若干备选类型中持有一个当前值，访问类型不匹配会失败或抛异常。选项 D 的表述“抛出 ｀std::bad_variant_access｀ 异常”正好符合该规则。A、B、C 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
