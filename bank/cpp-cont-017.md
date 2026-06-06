---
qid: cpp-cont-017
type: fill
kp: [cpp-containers]
difficulty: easy
answer_key: 未定义行为（迭代器失效）
---

阅读以下代码，在循环中调用 `v.push_back()` 可能导致什么问题？

```cpp
#include <vector>
std::vector<int> v = {1, 2, 3};
auto it = v.begin();
v.push_back(4);  // 可能触发扩容
std::cout << *it; // 此处 it 的状态是？
```

答：若 `push_back` 触发内存重新分配，则 `it` 已失效，解引用结果为 `______`。

## 解析

应填 `未定义行为（迭代器失效）`。`auto` 按模板实参推导规则工作，常会丢弃顶层 `const` 和引用，除非显式写成 `auto&`。 这个答案对应题干要求的标准名称、成员函数或复杂度写法。常见误区是填写相近但语义不同的接口，或漏掉作用域、大小写、下划线等精确拼写要求。
