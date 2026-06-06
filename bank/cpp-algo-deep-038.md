---
qid: cpp-algo-deep-038
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: B
---

下列代码计算两个集合的**交集**，前提条件是？

```cpp
std::vector<int> a{1,3,5,7,9};
std::vector<int> b{2,3,5,8,9};
std::vector<int> out;
std::set_intersection(a.begin(), a.end(),
                      b.begin(), b.end(),
                      std::back_inserter(out));
// out = ?
```

A. `out` 为空（`vector` 不是 `set`）
B. `out = {3, 5, 9}`；要求两个输入序列都**已排序**
C. `out = {1,3,5,7,9,2,3,5,8,9}`
D. 编译错误，需要传 `std::set`

---

**解析：**

`<algorithm>` 中的"set 系列"算法（`set_union` / `set_intersection` / `set_difference` / `set_symmetric_difference` / `includes` / `merge`）**作用于任意已排序序列**——名字里的 "set" 指数学集合而非 `std::set` 容器。

前提：两序列必须按**同一比较器**有序。输出同样按该比较器有序。算法用线性归并法实现，O(m+n)。

若用 `std::greater` 排序则 5 个算法的比较器也应传 `std::greater`。`std::back_inserter` 自动 `push_back`，适合大小未知的输出。
