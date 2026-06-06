---
qid: cpp-iter-014
type: single
kp: [cpp-iterators]
difficulty: easy
answer_key: D
---

以下代码存在什么问题？

```cpp
#include <vector>
std::vector<int> v = {1, 2, 3};
auto it = v.begin();
v.push_back(4);
std::cout << *it << std::endl;
```

A. 语法错误，无法编译
B. `push_back` 后 `it` 自动更新，输出 4
C. 输出 1，完全正确
D. 未定义行为：`push_back` 可能导致重新分配，`it` 已失效
