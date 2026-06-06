---
qid: cpp-real-nk-002
type: single
kp: [cpp-containers, cpp-stl-basics]
primary_kp: cpp-containers
difficulty: easy
answer_key: D
tags: [interview-real, nowcoder]
---

下列关于 `std::vector` 和 `std::list` 的对比，**错误**的是：

A. vector 内存连续，cache locality 好，list 节点分散，cache 命中率低
B. vector 中间插入是 O(n)，list 中间插入（已知迭代器）是 O(1)
C. vector 支持随机访问 `v[i]`，list 不支持
D. list 实际中间插入的性能总是优于 vector，因为是 O(1)

---

**解析：**

D 是常见误区。理论上 list 中间插入是 O(1)，vector 是 O(n)，但实测中：

1. **找到插入位置**：list 需要遍历（无随机访问），vector 直接 `v.begin() + i`
2. **cache miss**：list 节点分散在堆上，遍历时每个节点都是一次 cache miss；vector 连续内存，预取友好
3. **内存分配**：list 每个节点都要 `new`，vector 是批量分配

实测中，对于小型对象（如 int），即使在中间插入 10000 次，vector 也常常快于 list。Bjarne Stroustrup 在多次演讲中演示过该现象。只有当元素移动成本极高（大对象 + 不可移动）时 list 才有优势。

**来源：** 牛客网 C++ 面试题 / Bjarne Stroustrup GoingNative 2012 演讲

## Explanation

正确答案是 D。
关键是说明正确选项成立的 C++ 规则，以及其他选项忽略的边界条件。
常见误区是只记结论，不解释代码行为、编译行为或复杂度前提。
