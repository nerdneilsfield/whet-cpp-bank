---
qid: cpp-cpp17-014
type: fill
kp: [cpp-cpp14-17]
difficulty: easy
answer_key: "100"
---

# 代码阅读：make_unique 与解引用

```cpp
#include <iostream>
#include <memory>

int main() {
    auto p = std::make_unique<int>(100);
    std::cout << *p << "\n";
}
```

程序输出：`_______`

（填写整数结果，不含换行符）

## 解析

应填 `100`。`auto` 按模板实参推导规则工作，常会丢弃顶层 `const` 和引用，除非显式写成 `auto&`。 这个答案对应题干要求的标准名称、成员函数或复杂度写法。常见误区是填写相近但语义不同的接口，或漏掉作用域、大小写、下划线等精确拼写要求。
