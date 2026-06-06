---
qid: cpp-real-nk-008
type: single
kp: [cpp-stl-basics, cpp-containers]
primary_kp: cpp-stl-basics
difficulty: hard
answer_key: B
tags: [interview-real, nowcoder]
---

关于 `std::deque` 的内部实现，下列描述正确的是：

A. deque 是单一连续内存数组，两端预留空间
B. deque 由一个**中央控制器**（指针数组，称 map）管理多个**固定大小的缓冲区**，缓冲区之间不连续
C. deque 是双向链表，每个节点是一个元素
D. deque 内部就是 `vector<vector<T>>`，可变缓冲区

---

**解析：**

`deque` 的实现（以 GCC libstdc++ 为例）：

- **中央控制器（map）**：一个指针数组，每个指针指向一段缓冲区
- **缓冲区**：固定大小的连续内存块（例如 GCC 中元素 ≤ 8 字节时缓冲区放 16 个元素）
- 两端 push 时，若当前缓冲区满，新分配缓冲区并更新 map；map 满时重新分配 map

这种结构使得：
- `operator[]` 是 O(1)（两次寻址：map → buffer → 元素）但常数比 vector 大
- 两端 push/pop 是 O(1) 均摊
- 迭代器较复杂（要保存 cur/first/last/node 四个指针）
- 中间插入仍是 O(n)

这就是为什么 `std::stack` 和 `std::queue` 的默认底层容器是 deque 而非 vector——避免 vector 扩容时的大块内存拷贝。

**来源：** 牛客网 C++ STL 源码面试题 / 《STL 源码剖析》侯捷

## Explanation

正确答案是 B。
关键是说明正确选项成立的 C++ 规则，以及其他选项忽略的边界条件。
常见误区是只记结论，不解释代码行为、编译行为或复杂度前提。
