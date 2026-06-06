---
qid: cpp-algo-deep-002
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: B
---

下列代码意图去重，实际输出是？

```cpp
std::vector<int> v{1, 2, 1, 3, 2, 1, 4};
v.erase(std::unique(v.begin(), v.end()), v.end());
for (auto x : v) std::cout << x << " ";
```

A. `1 2 3 4`
B. `1 2 1 3 2 1 4`
C. `1 2 3 2 1 4`
D. 未定义行为

---

**解析：**

`std::unique` 只移除**相邻**重复元素，并不会做全局去重。因此对未排序的 `v`，每个相邻位置都不相等，没有任何元素被消除，输出原样。

正确做法：先排序再 unique：

```cpp
std::sort(v.begin(), v.end());
v.erase(std::unique(v.begin(), v.end()), v.end());
// → 1 2 3 4
```

或直接用 `std::set` / `std::unordered_set`。注意 `std::unique` 同样返回新逻辑末尾迭代器，配合 `erase` 才能真正缩容。
