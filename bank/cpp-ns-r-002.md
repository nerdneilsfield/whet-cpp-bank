---
qid: cpp-ns-r-002
type: single
kp: [cpp-preprocessor]
difficulty: easy
answer_key: A
---

# 代码阅读：宏不做类型检查

下列代码能否编译？输出什么？

```cpp
#include <iostream>
#define DOUBLE(x) ((x) + (x))

int main() {
    std::string s = "ab";
    std::cout << DOUBLE(s) << std::endl;
}
```

A. 编译成功，输出 `abab`（宏对 `std::string` 展开为字符串拼接，不做类型检查）  
B. 编译错误：宏只能作用于数值类型  
C. 编译成功，输出 `ab ab`（自动在中间插入空格）  
D. 运行时抛出异常：`string` 不支持 `+` 运算符
