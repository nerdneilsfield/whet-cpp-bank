---
qid: cpp-stl-r-002
type: single
kp: [cpp-stl-basics]
difficulty: easy
answer_key: B
---

# 代码阅读：string::find 返回 npos 的处理

下列代码输出什么？

```cpp
#include <string>
#include <iostream>

int main() {
    std::string s = "hello world";
    size_t pos = s.find("xyz");
    if (pos == std::string::npos) {
        std::cout << "not found" << std::endl;
    } else {
        std::cout << "found at " << pos << std::endl;
    }
}
```

A. `found at 18446744073709551615`（因为 `npos` 是 `size_t` 最大值）  
B. `not found`  
C. 编译错误：`size_t` 与 `std::string::npos` 类型不匹配，不能用 `==` 比较  
D. 运行时抛出 `std::out_of_range` 异常
