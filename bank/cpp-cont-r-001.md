---
qid: cpp-cont-r-001
type: single
kp: [cpp-containers]
difficulty: easy
answer_key: "C"
---

### 题目

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

## Explanation

正确答案是 C。`auto` 按模板实参推导规则工作，常会丢弃顶层 `const` 和引用，除非显式写成 `auto&`。选项 C 的表述“｀1:one 2:two 3:three 4:four｀（升序）”正好符合该规则。A、B、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
