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

## Explanation

正确答案是 B：set_intersection 作用于任意已排序序列，不要求容器类型是 std::set。两个输入均已升序，公共元素依次为 3、5、9，因此输出交集 `{3,5,9}`。关键前提是两边必须按同一比较器排序，否则算法的归并过程会得到不可靠结果。
