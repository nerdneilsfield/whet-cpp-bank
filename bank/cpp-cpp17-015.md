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

## Explanation

正确答案是 C。`auto` 按模板实参推导规则工作，常会丢弃顶层 `const` 和引用，除非显式写成 `auto&`。选项 C 的表述“｀95｀”正好符合该规则。A、B、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
