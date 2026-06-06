---
qid: cpp-stl-r-003
type: single
kp: [cpp-stl-basics]
difficulty: easy
answer_key: A
---

# 代码阅读：vector 初始化内容

下列代码输出什么？

```cpp
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v(3, 5);
    for (int x : v) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}
```

A. `5 5 5`  
B. `3 5 0`  
C. `0 0 0`（值初始化忽略第二个参数）  
D. 编译错误：`vector<int>` 构造函数不接受两个整型参数
