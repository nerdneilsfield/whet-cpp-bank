---
qid: cpp-stl-r-001
type: single
kp: [cpp-stl-basics]
difficulty: easy
answer_key: C
---

# 代码阅读：vector 遍历时 push_back 导致迭代器失效

下列代码的行为是什么？

```cpp
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {1, 2, 3};
    for (auto it = v.begin(); it != v.end(); ++it) {
        if (*it == 2) {
            v.push_back(10); // 在遍历中插入元素
        }
    }
    std::cout << v.size() << std::endl;
}
```

A. 输出 `4`，程序正常结束  
B. 输出 `5`，程序正常结束  
C. 未定义行为：`push_back` 可能触发重新分配，使 `it` 和 `v.end()` 失效  
D. 编译错误：不能在范围 for 循环中调用 `push_back`
