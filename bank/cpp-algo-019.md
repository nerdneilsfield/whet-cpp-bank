---
qid: cpp-algo-019
type: multi
kp: [cpp-algorithms]
difficulty: easy
answer_key: [B, D]
---

以下哪些说法关于 `std::remove` / `std::remove_if` 是**正确**的？（多选）

A. 调用 `std::remove` 后，容器的 `size()` 立即减小
B. `std::remove` 并不真正删除元素，只是将不需要的元素移到范围末尾
C. `std::remove` 返回被移除元素的个数
D. 要真正删除元素，需要配合容器的 `erase` 成员函数（erase-remove idiom）

## 解析

正确答案为 B、D。A项“调用 `std::remove` 后，容器的 `size()` 立即减小”不是正确项；B项“`std::remove` 并不真正删除元素，只是将不需要的元素移到范围末尾”是正确项；C项“`std::remove` 返回被移除元素的个数”不是正确项；D项“要真正删除元素，需要配合容器的 `erase` 成员函数（erase-remove idiom）”是正确项。常见误区是只看到相似术语就全选，实际应逐项检查标准规则和题干限定。STL 算法通常只操作迭代器区间，前置条件、返回值和是否改变容器大小要分开判断。
