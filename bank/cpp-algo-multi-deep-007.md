---
qid: cpp-algo-multi-deep-007
type: multi
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: [A, B, C]
---

关于 set 系列算法（`set_union` 等），下列哪些**正确**？（多选）

A. 全部要求两输入序列已按**同一比较器**排序
B. 输出序列同样按该比较器有序
C. 时间复杂度 O(m + n)
D. 输入必须是 `std::set` 容器

---

**解析：**

- A ✅：set 算法基于归并，前提是输入有序。
- B ✅：归并输出天然有序。
- C ✅：线性归并，最多 2(m+n)−1 次比较。
- D ❌：名字里 "set" 指数学集合；任何已排序的范围（vector/array/list 等）都可用。`set_*` 算法接受迭代器对，与容器类型无关。

对未排序输入：行为未定义；可先 `std::sort` 再调，或用 `std::unordered_set` 做交集（需手动循环）。
