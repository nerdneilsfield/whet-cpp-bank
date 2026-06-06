---
qid: cpp-cpp17-r-004
type: single
kp: [cpp-cpp14-17]
difficulty: easy
answer_key: "D"
---

### 题目

阅读以下代码，存在什么问题？

```cpp
#include <string_view>
#include <iostream>

std::string_view get_greeting() {
    std::string s = "Hello, World!";
    return s;   // 返回 string_view
}

int main() {
    auto sv = get_greeting();
    std::cout << sv;   // 行 A
}
```

A. 编译错误：`string` 不能隐式转换为 `string_view`
B. 正常输出 `Hello, World!`
C. 输出空字符串
D. 未定义行为：`string_view` 引用已销毁的局部变量

## Explanation

`std::string_view` 是**非拥有**视图，内部持有指向字符串数据的指针。函数返回时局部 `std::string s` 被销毁，内存释放，但返回的 `string_view` 仍持有指向该内存的悬空指针。行 A 访问该指针是未定义行为（可能崩溃、输出乱码或"看似正常"）。`string_view` 的生命周期必须不超过其所指向的字符串。
