---
qid: cpp-algo-deep-001
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: C
---

下列代码的输出是？

```cpp
std::vector<int> v{1, 2, 3, 2, 4, 2, 5};
auto it = std::remove(v.begin(), v.end(), 2);
std::cout << v.size() << " ";
for (auto x : v) std::cout << x << " ";
```

A. `4 1 3 4 5`
B. `7 1 3 4 5 2 2 2`
C. `7 1 3 4 5 ? ? ?`（后三个元素的值未指定，可能是 4/2/5 等残留）
D. 编译错误，`std::remove` 不能用于 vector

## Explanation

正确答案是 C：std::remove 只把不等于 2 的元素前移，并返回新的逻辑末尾，不会改变 vector 的 size。前三个尾部位置仍属于容器，但其值不再有语义保证，所以只能说是有效但未指定。误区是把 remove 当成 erase；真正缩容要接 v.erase(new_end, v.end())，或 C++20 用 std::erase。
