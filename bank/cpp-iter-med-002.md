---
qid: cpp-iter-med-002
type: single
kp: [cpp-iterators]
difficulty: medium
answer_key: B
---

下列代码 `*it.base()` 的值是多少？

```cpp
std::vector<int> v = {10, 20, 30, 40, 50};
auto rit = std::find(v.rbegin(), v.rend(), 30);  // 指向 30
auto it  = rit.base();
std::cout << *it;
```

A. `30`，`base()` 返回与 `rit` 指向同一个元素的正向迭代器
B. `40`，`base()` 返回的正向迭代器指向 `rit` 所指元素的**下一个**位置
C. `20`，`base()` 返回的正向迭代器指向 `rit` 所指元素的**前一个**位置
D. 行为未定义，`base()` 返回的迭代器不能解引用

---

**解析：**

`std::reverse_iterator::base()` 的关系是 `&*r == &*(r.base() - 1)`，即 reverse_iterator `r` 所指的元素，对应于 `r.base() - 1`，而 `r.base()` 本身指向**下一个位置**。

直观理解：reverse_iterator 是 "正向迭代器的镜像"，它把 `rbegin()` 映射为 `end()`、把 `rend()` 映射为 `begin()`。要让 `rbegin()` 指向最后一个元素，而 `rbegin().base() == end()` 又必须是"末尾后一位"，唯一一致的方式就是这种"偏移 1 位"的关系。

所以 `rit` 找到 `30`，`rit.base()` 指向 `40`，`*it` 得到 `40`。

这个偏移在 `erase`/`insert` 配合 `reverse_iterator` 时会咬人——若想删除 `rit` 所指元素，正确写法是 `v.erase(std::next(rit).base())` 或 `v.erase((rit + 1).base())`，不能直接 `v.erase(rit.base())`（那会删错位置）。
