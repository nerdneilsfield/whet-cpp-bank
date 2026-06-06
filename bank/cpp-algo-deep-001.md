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

---

**解析：**

`std::remove` **不真正删除元素**，也不改变容器大小。它把不等于 `2` 的元素**前移**覆盖，返回新逻辑末尾的迭代器；尾部 `[it, v.end())` 区间的元素值是**未指定**的（unspecified，但被移动赋值后处于有效但未指定的状态）。

`v.size()` 仍是 `7`，前 4 个元素是 `1 3 4 5`，后 3 个可能是移动残留值。要真正删除需用 erase-remove 惯用法：

```cpp
v.erase(std::remove(v.begin(), v.end(), 2), v.end());
// C++20 起更简洁：
std::erase(v, 2);
```
