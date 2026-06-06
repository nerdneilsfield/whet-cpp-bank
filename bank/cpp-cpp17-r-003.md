---
qid: cpp-cpp17-r-003
type: single
kp: [cpp-cpp14-17]
difficulty: easy
answer_key: "A"
---

### 题目

阅读以下代码，程序输出是什么？

```cpp
#include <iostream>

template<typename T>
void print_type(T val) {
    if constexpr (std::is_integral_v<T>) {
        std::cout << "int:" << val * 2;
    } else {
        std::cout << "other:" << val;
        // 假设 T=int 时此分支不编译
        static_assert(!std::is_integral_v<T>, "not int");
    }
}

int main() {
    print_type(5);
    std::cout << " ";
    print_type(3.14);
}
```

A. `int:10 other:3.14`
B. 编译错误：`static_assert` 对 `T=int` 失败
C. `int:10 int:6`
D. 运行时错误

## Explanation

`if constexpr` 在编译期选择分支，**未选中的分支不被实例化**。当 `T=int` 时，`else` 分支整体不编译，`static_assert(!std::is_integral_v<int>, ...)` 不触发。当 `T=double` 时，`if` 分支不编译，`else` 分支输出 `other:3.14`。最终输出 `int:10 other:3.14`。
