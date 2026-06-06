---
qid: cpp-cpp17-013
type: fill
kp: [cpp-cpp14-17]
difficulty: easy
answer_key: "pair<int, double>"
---

# 代码阅读：CTAD 推导类型

```cpp
#include <utility>
auto p = std::pair{42, 3.14};
```

C++17 CTAD 推导后，`p` 的类型是：

`std::_______`

（填写完整模板特化类型，如 `pair<int, int>`）

## Explanation

应填 `pair<int, double>`。`auto` 按模板实参推导规则工作，常会丢弃顶层 `const` 和引用，除非显式写成 `auto&`。 这个答案对应题干要求的标准名称、成员函数或复杂度写法。常见误区是填写相近但语义不同的接口，或漏掉作用域、大小写、下划线等精确拼写要求。
