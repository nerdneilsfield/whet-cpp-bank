---
qid: cpp-cont-013
type: single
kp: [cpp-containers]
difficulty: easy
answer_key: A
---

阅读以下代码，`it` 指向何处？

```cpp
#include <map>
std::map<int, int> m = {{1,10},{2,20},{3,30}};
auto it = m.find(2);
```

A. 指向键为 `2`、值为 `20` 的元素
B. 指向 `m.end()`
C. 指向键为 `1` 的元素
D. 未定义行为

## Explanation

正确答案是 A。`auto` 按模板实参推导规则工作，常会丢弃顶层 `const` 和引用，除非显式写成 `auto&`。选项 A 的表述“指向键为 ｀2｀、值为 ｀20｀ 的元素”正好符合该规则。B、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
