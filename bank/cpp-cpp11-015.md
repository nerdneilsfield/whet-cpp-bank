---
qid: cpp-cpp11-015
type: fill
kp: [cpp-cpp11]
difficulty: easy
answer_key: "5"
---

# 代码阅读：initializer_list 求和

阅读以下代码，输出是多少？

```cpp
#include <iostream>
#include <initializer_list>

int sum(std::initializer_list<int> lst) {
    int s = 0;
    for (auto v : lst) s += v;
    return s;
}

int main() {
    std::cout << sum({1, 2, 2});
}
```

输出为：___

## Explanation

应填 `5`。`auto` 按模板实参推导规则工作，常会丢弃顶层 `const` 和引用，除非显式写成 `auto&`。 这个答案对应题干要求的标准名称、成员函数或复杂度写法。常见误区是填写相近但语义不同的接口，或漏掉作用域、大小写、下划线等精确拼写要求。
