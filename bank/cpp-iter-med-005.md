---
qid: cpp-iter-med-005
type: single
kp: [cpp-iterators]
difficulty: medium
answer_key: D
---

下列代码运行结果是？

```cpp
std::vector<int> src = {1, 2, 3, 4, 5};
std::vector<int> dst;                       // 注意：dst 是空的
std::copy(src.begin(), src.end(),
          std::back_inserter(dst));
// 之后想再复制一遍到 dst 前部：
std::copy(src.begin(), src.end(), dst.begin());
```

A. `dst` 最终内容是 `{1,2,3,4,5,1,2,3,4,5}`
B. 编译错误：`dst.begin()` 在空 `dst` 上不可用
C. `dst` 最终内容是 `{1,2,3,4,5}`（第二次 copy 把前五个覆盖成自身）
D. 第二次 `copy` 是未定义行为：`std::copy` 写入 `dst.begin()` 时不会自动扩容，会越界写

---

**解析：**

A、C 两个答案都基于一个错误前提：`std::copy(src.begin(), src.end(), dst.begin())` 会"自动追加"或"安全覆盖"。实际上 `std::copy` 的目标迭代器只是普通输出迭代器，它做的就是 `*d++ = *s++;`，**不会改变容器大小**。

第一次 `back_inserter(dst)` 的 copy 后，`dst` 大小是 5，`dst.begin()` 指向第一个元素，但 `dst` 的容量也可能正好是 5。第二次 `copy` 从 `dst.begin()` 开始写 5 个元素：写第 1 个覆盖原 `dst[0]`，写到第 6 个就越过了 `dst.size()` 的边界——这是对 `vector` 已分配区域之外的位置赋值，UB。即便 capacity 大于 size，越过 `end()` 写仍是访问"分配但未构造"的存储，仍是 UB。

正确做法：要追加用 `back_inserter`；要覆盖前先 `dst.resize(src.size())` 保证目标区间有效；或直接用 `dst = src;` / `dst.assign(src.begin(), src.end())`。这条规则同样适用于 `std::transform`、`std::generate_n` 等所有写入型算法——**迭代器适配器**（如 `back_inserter`）才负责扩容，原始迭代器只负责写已有位置。

## 解析

正确答案是 D，对应“第二次 copy 是未定义行为：std::copy 写入 dst.begin() 时不会自动扩容，会越界写”。本题考查迭代器类别、失效规则或迭代移动语义，关键是看容器操作后原迭代器是否仍指向有效元素。其他选项容易混淆相关概念：A 项“dst 最终内容是 {1,2,3,4,5,1,2,3,4,5}”不满足题干要求；B 项“编译错误：dst.begin() 在空 dst 上不可用”不满足题干要求；C 项“dst 最终内容是 {1,2,3,4,5}（第二次 copy 把前五个覆盖成自身）”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
