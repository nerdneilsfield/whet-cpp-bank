---
qid: cpp-stl-012
type: single
kp: [cpp-stl-basics]
difficulty: easy
answer_key: A
---

以下哪段代码正确地用范围 for 遍历 `std::vector<int>` 并打印每个元素？

```cpp
std::vector<int> v = {1, 2, 3};
```

A. `for (int x : v) { std::cout << x << "\n"; }`
B. `for (int x in v) { std::cout << x << "\n"; }`
C. `for (int i = 0; i < v; i++) { std::cout << v << "\n"; }`
D. `foreach (int x : v) { std::cout << x << "\n"; }`
