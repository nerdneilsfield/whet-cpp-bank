---
qid: cpp-iter-short-001
type: short
kp: [cpp-iterators]
difficulty: medium
rubric:
  - 列出五种迭代器类别：input, output, forward, bidirectional, random access（C++20 加 contiguous）
  - 说明每类支持的操作（如 random access 支持 +n、随机比较）
  - 指出算法对迭代器类别有要求（如 sort 需要随机访问）
  - 给出对应容器示例（vector 的迭代器是 random access，list 是 bidirectional）
---
请列举 C++ 标准库中的几种迭代器类别，并说明它们能力上的差异。

---

**参考答案：**

C++ 迭代器按能力分为五类（C++20 增加 contiguous）：input（单遍只读前进）、output（单遍只写前进）、forward（可多遍读写，仅 ++）、bidirectional（再加 --）、random access（再加 +n、it[n]、it1 < it2 等 O(1) 跳转），以及 C++20 的 contiguous iterator（内存连续，可转 raw pointer）。算法对迭代器要求不同：`std::sort` 需要 random access，所以可用于 vector/deque/数组但不能直接对 list 排序；`list` 提供自身的 `sort()` 成员。迭代器类别决定容器与算法的搭配。