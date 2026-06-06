---
qid: cpp-cross-tc-004
type: single
kp: [cpp-templates, cpp-containers]
difficulty: easy
answer_key: D
---

以下代码输出是什么？

```cpp
#include <iostream>
#include <map>
#include <vector>
#include <string>

int main() {
    std::map<std::string, std::vector<int>> m;
    m["b"] = {3, 4};
    m["a"] = {1, 2};
    m["c"] = {5};

    for (const auto& [key, vec] : m) {
        std::cout << key << ":";
        for (int v : vec) std::cout << v;
        std::cout << "\n";
    }
    return 0;
}
```

A. `b:34\na:12\nc:5\n`（按插入顺序）  
B. `c:5\nb:34\na:12\n`（逆序）  
C. 编译错误，`map` 的值不能是 `vector`  
D. `a:12\nb:34\nc:5\n`（按 key 字典序）

<!--
std::map 以 key 的 < 运算符排序，字符串按字典序：a < b < c。
遍历输出顺序固定为 a、b、c，与插入顺序无关。
-->

## 解析

D 正确：`std::map` 按 key 的比较函数维护有序结构，默认用 `operator<`。字符串 key 的顺序是 `a`、`b`、`c`，与插入顺序无关。关键误区是把 `map` 当成保持插入顺序的容器；若需要插入顺序应使用其他结构。
