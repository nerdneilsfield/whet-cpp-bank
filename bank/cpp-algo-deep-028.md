---
qid: cpp-algo-deep-028
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: B
---

下列代码在 `std::set` 上查找元素，最优写法是？

```cpp
std::set<int> s{1,2,3,4,5,6,7,8,9};
int key = 5;
???
```

A. `auto it = std::find(s.begin(), s.end(), key); // O(log n)`
B. `auto it = s.find(key); // O(log n)`
C. `auto it = std::binary_search(s.begin(), s.end(), key); // 返回 iterator`
D. 两种都一样快，`std::find` 在 set 上会自动用二分

## Explanation

正确答案是 B：std::set::find 会利用红黑树结构，时间复杂度 O(log n)。通用 std::find 只做线性扫描，不会自动利用 set 的有序结构。binary_search 返回 bool 而不是迭代器，也不是最优成员查找方式。
