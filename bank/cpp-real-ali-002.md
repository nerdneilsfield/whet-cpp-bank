---
qid: cpp-real-ali-002
type: single
kp: [cpp-containers]
primary_kp: cpp-containers
difficulty: hard
answer_key: C
tags: [interview-real, alibaba]
---
关于 `std::map` 选择红黑树而非 AVL 树的理由，以下说法最准确的是：

A. AVL 树插入和删除也是 O(log n)，红黑树也是 O(log n)，实际上没有区别
B. 红黑树的查找比 AVL 更快，所以 C++ 标准选择了红黑树
C. 红黑树的插入/删除旋转次数更少（均摊 O(1) vs AVL 的 O(log n)），更适合容器场景
D. AVL 树实现比红黑树复杂，C++ 标准委员会选择了更简单的实现

---

**解析：**

选 C。红黑树与 AVL 树的选择本质是 **"查找 vs 修改"的工程权衡**。

AVL 树要求任意节点左右子树高度差 ≤1，平衡极其严格。这意味着：
- 每次插入/删除最多需要 O(log n) 次旋转来恢复平衡
- 查找性能最优（严格平衡 → 树高 ≈ 1.44log₂n）

红黑树只要求：
- 任一节点到叶子的路径上黑色节点数相同（黑高相等）
- 不允许连续红色节点
- 树高 ≤ 2log₂(n+1)，查找略慢

但红黑树插入/删除的**旋转次数均摊为 O(1)**（至多 2-3 次旋转），而 AVL 需要回溯到根的 O(log n) 次。对 `std::map` 这种**增删改查混合**的通用容器，红黑树更优。

如果场景是**极少修改、极高频率查询**（如数据库索引），AVL 或跳表可能更好——但这不是 C++ std::map 的目标场景。

**来源：** 阿里 C++ 面试追问链（参考：huihut/interview、cs-offer）

## Explanation

正确答案是 C。
选 C。红黑树与 AVL 树的选择本质是 "查找 vs 修改"的工程权衡。
如果场景是极少修改、极高频率查询（如数据库索引），AVL 或跳表可能更好——但这不是 C++ std::map 的目标场景。
