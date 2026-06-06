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
