---
qid: cpp-cpp17-015
type: single
kp: [cpp-cpp14-17]
difficulty: easy
answer_key: C
---

# 代码阅读：结构化绑定遍历 map

```cpp
#include <iostream>
#include <map>

int main() {
    std::map<std::string, int> scores = {{"Alice", 90}, {"Bob", 85}};
    for (auto& [name, score] : scores) {
        score += 5;
    }
    std::cout << scores["Alice"] << "\n";
}
```

程序输出什么？

A. `90`
B. `85`
C. `95`
D. 编译错误：结构化绑定不能绑定 map 的元素
