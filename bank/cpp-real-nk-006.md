---
qid: cpp-real-nk-006
type: single
kp: [cpp-stl-basics, cpp-containers]
primary_kp: cpp-stl-basics
difficulty: easy
answer_key: D
tags: [interview-real, nowcoder]
---

```cpp
std::set<int> s = {1, 2, 2, 3, 3, 3};
std::multiset<int> ms = {1, 2, 2, 3, 3, 3};

std::cout << s.size() << " " << ms.size() << std::endl;
std::cout << s.count(3) << " " << ms.count(3) << std::endl;
```

输出是：

A. `6 6` 和 `3 3`
B. `3 3` 和 `1 3`
C. `6 3` 和 `1 3`
D. `3 6` 和 `1 3`

---

**解析：**

- `set` 是有序集合，**不允许重复键**，初始化时 `{1,2,2,3,3,3}` 实际只插入 `{1,2,3}`，size=3
- `multiset` **允许重复键**，全部插入，size=6
- `s.count(3)` 在 set 中只能是 0 或 1，这里是 1
- `ms.count(3)` 在 multiset 中返回所有等于 3 的元素数，这里是 3

`multiset::count` 的时间复杂度是 O(log n + k)，k 为匹配元素数。底层都是红黑树。

**来源：** 牛客网 C++ STL 基础面试题

## Explanation

正确答案是 D。
set 是有序集合，不允许重复键，初始化时 {1,2,2,3,3,3} 实际只插入 {1,2,3}，size=3 multiset 允许重复键，全部插入，size=6 s.count(3) 在 set 中只能是 0 或 1，这里是 1 ms.count(3) 在 multiset 中返回所有等于 3 的元素数，这里是 3 multiset::count 的时间复杂度是 O(log n + k)，k 为匹配元素数。底层都是红黑树。
