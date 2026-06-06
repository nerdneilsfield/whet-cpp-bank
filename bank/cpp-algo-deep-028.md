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

---

**解析：**

`std::find` 是**通用线性搜索** O(n)，不会因为容器是 `set` 而切换为二分——它只看迭代器类别。

`std::set::find` 是成员函数，利用内部红黑树结构，O(log n)。同理 `map::find`、`unordered_set::find`（O(1) 平均）应**优先用成员函数**。

`std::binary_search` 返回 `bool` 不返回迭代器；C 写法编译错误。

C++20 起 `std::ranges::contains`（C++23 实际加入）提供更便利的语法，但对关联容器仍应优先成员函数。
