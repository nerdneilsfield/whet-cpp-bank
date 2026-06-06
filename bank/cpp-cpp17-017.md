---
qid: cpp-cpp17-017
type: single
kp: [cpp-cpp14-17]
difficulty: easy
answer_key: A
---

# 代码阅读：std::optional 链式访问

```cpp
#include <iostream>
#include <optional>

std::optional<int> divide(int a, int b) {
    if (b == 0) return std::nullopt;
    return a / b;
}

int main() {
    auto result = divide(10, 2);
    if (result.has_value()) {
        std::cout << *result << "\n";
    } else {
        std::cout << "error\n";
    }
}
```

程序输出什么？

A. `5`
B. `error`
C. `10`
D. 运行时抛出异常

## Explanation

正确答案是 A。`auto` 按模板实参推导规则工作，常会丢弃顶层 `const` 和引用，除非显式写成 `auto&`。选项 A 的表述“｀5｀”正好符合该规则。B、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
