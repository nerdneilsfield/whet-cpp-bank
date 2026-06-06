---
qid: cpp-cpp17-r-001
type: single
kp: [cpp-cpp14-17]
difficulty: easy
answer_key: "B"
---

### 题目

阅读以下代码，程序输出是什么？

```cpp
#include <iostream>
#include <map>

int main() {
    std::map<std::string, int> scores = {{"Alice", 90}, {"Bob", 75}};
    for (auto& [name, score] : scores) {
        score += 5;
    }
    for (auto [name, score] : scores) {
        std::cout << name << ":" << score << " ";
    }
}
```

A. `Alice:90 Bob:75`
B. `Alice:95 Bob:80`
C. 编译错误：结构化绑定不能绑定到 `map`
D. `Alice:95 Bob:80` 但顺序不确定

## Explanation

C++17 结构化绑定 `auto& [name, score]` 解包 `map` 的 `value_type`（即 `std::pair<const std::string, int>`）。`score` 是引用，`score += 5` 修改 map 中的值。第二个循环按 `map` 的有序迭代输出（字典序），Alice < Bob，输出 `Alice:95 Bob:80`。`map` 按 key 有序，顺序确定。
