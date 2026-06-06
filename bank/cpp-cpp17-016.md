---
qid: cpp-cpp17-016
type: single
kp: [cpp-cpp14-17]
difficulty: easy
answer_key: B
---

# 代码阅读：if constexpr 分支

```cpp
#include <iostream>
#include <type_traits>

template<typename T>
void print_type(T val) {
    if constexpr (std::is_integral_v<T>) {
        std::cout << "integer: " << val << "\n";
    } else {
        std::cout << "other: " << val << "\n";
    }
}

int main() {
    print_type(42);
    print_type(3.14);
}
```

程序输出什么？

A. `other: 42` 和 `other: 3.14`
B. `integer: 42` 和 `other: 3.14`
C. `integer: 42` 和 `integer: 3.14`
D. 编译错误：`if constexpr` 不能用于模板函数
