---
qid: cpp-cont-011
type: single
kp: [cpp-containers]
difficulty: easy
answer_key: C
---

阅读以下代码，输出是什么？

```cpp
#include <map>
#include <iostream>
int main() {
    std::map<std::string, int> m;
    m["a"] = 1;
    m["b"] = 2;
    m["c"] = 3;
    for (auto& [k, v] : m) {
        std::cout << k << v;
    }
}
```

A. `c3b2a1`
B. 输出顺序不确定
C. `a1b2c3`
D. 编译错误

## 解析

正确答案是 C。`auto` 按模板实参推导规则工作，常会丢弃顶层 `const` 和引用，除非显式写成 `auto&`。选项 C 的表述“｀a1b2c3｀”正好符合该规则。A、B、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
