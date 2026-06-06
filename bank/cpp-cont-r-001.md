---
qid: cpp-cont-r-001
type: single
kp: [cpp-containers]
difficulty: easy
answer_key: "C"
---

## 题目

以下代码输出什么？

```cpp
#include <map>
#include <iostream>

int main() {
    std::map<int, std::string> m;
    m[3] = "three";
    m[1] = "one";
    m[4] = "four";
    m[2] = "two";
    for (auto& [k, v] : m) {
        std::cout << k << ":" << v << " ";
    }
}
```

A. `3:three 1:one 4:four 2:two`（插入顺序）
B. `4:four 3:three 2:two 1:one`（降序）
C. `1:one 2:two 3:three 4:four`（升序）
D. 输出顺序未定义

## 解析

`std::map` 是基于红黑树的有序关联容器，按键的升序（`operator<`）排列。遍历时始终按键升序输出，与插入顺序无关。
