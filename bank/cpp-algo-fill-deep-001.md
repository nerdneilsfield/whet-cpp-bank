---
qid: cpp-algo-fill-deep-001
type: fill
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: ["erase-remove", "erase_remove", "erase remove", "erase remove idiom"]
---

C++ 中用 `v.erase(std::remove(v.begin(), v.end(), x), v.end());` 真正从 `std::vector` 删除等于 `x` 的所有元素，这一惯用法被称为 _______（请填惯用法名，英文，可写空格或连字符）。

## 解析

答案是 erase-remove idiom。std::remove 只把不需要删除的元素前移，并返回新的逻辑末尾，不会改变 vector 的实际大小。随后调用 erase 删除 `[new_end, end)` 这段尾部无效区间，才真正缩短容器。误区是认为 remove 已经完成物理删除。
