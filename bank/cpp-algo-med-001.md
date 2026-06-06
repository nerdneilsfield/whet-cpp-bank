---
qid: cpp-algo-med-001
type: single
kp: [cpp-algorithms]
difficulty: medium
answer_key: C
---

下列代码执行后 `v` 的内容是？

```cpp
std::vector<int> v = {1, 2, 3, 2, 4, 2, 5};
std::remove(v.begin(), v.end(), 2);
// 注意：没有 erase
```

A. `{1, 3, 4, 5}`，size 变成 4
B. `{1, 3, 4, 5, 0, 0, 0}`，size 仍是 7
C. `{1, 3, 4, 5, ?, ?, ?}`，size 仍是 7；末尾三个元素值未指定（valid-but-unspecified）
D. `{1, 2, 3, 2, 4, 2, 5}`，`remove` 仅返回新逻辑末尾，原容器内容不变

---

**解析：**

`std::remove` 是**算法**，不是成员函数，它对容器结构一无所知，**做不到改变 size**。它做的是：把不被移除的元素逐个向前搬移（通过移动赋值），并返回一个迭代器 `new_end`，标记新逻辑末尾。

搬移后，区间 `[begin, new_end)` 是"剩下应保留的元素"，区间 `[new_end, end)` 是"被搬空的尾巴"——这些位置的元素**有效但值未指定**（valid-but-unspecified state，move-from 后的标准约定）。它们不是 0，不是原值，也不是已析构。

`v.size()` 仍是 7。要真正缩容，必须配合 `erase`：

```cpp
v.erase(std::remove(v.begin(), v.end(), 2), v.end());   // erase-remove idiom
```

C++20 引入了 `std::erase(v, 2)` 和 `std::erase_if(v, pred)` 直接做这件事，省去 idiom。这条机制是 C++ 算法/容器分离设计的代价：算法只看迭代器，无法回头操作容器。

## Explanation

正确答案为 C，因为“`{1, 3, 4, 5, ?, ?, ?}`，size 仍是 7；末尾三个元素值未指定（valid-but-unspecified）”符合题干所问的 C++ 规则或代码执行结果。A、B、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。STL 算法通常只操作迭代器区间，前置条件、返回值和是否改变容器大小要分开判断。
