---
qid: cpp-algo-short-001
type: short
kp: [cpp-algorithms]
difficulty: medium
rubric:
  - 解释 std::remove 不真正删除元素，而是将"保留"元素移到前部、返回新逻辑尾迭代器
  - 指出之后必须配合容器的 erase 才能真正缩短容器（erase-remove 惯用法）
  - 给出代码示例 `v.erase(std::remove(v.begin(),v.end(),x), v.end());`
  - 提到 C++20 引入 std::erase / erase_if 简化此惯用法
---
请解释 STL 中的 erase-remove 惯用法，并说明为什么 `std::remove` 单独使用并不能真正删除元素。

---

**参考答案：**

`std::remove`（以及 `std::remove_if`）并不修改容器大小，它只是把满足保留条件的元素前移、把要"删除"的元素覆盖掉，并返回新的逻辑尾迭代器；尾部到容器实际尾之间的元素值未定义。要真正缩短容器，必须再调用容器的 `erase` 把这段废弃区间删掉：

```cpp
v.erase(std::remove(v.begin(), v.end(), x), v.end());
```

这就是 erase-remove 惯用法。C++20 提供 `std::erase(v, x)` 和 `std::erase_if(v, pred)` 来直接完成这件事，更加简洁。

## 解析

本题应围绕关键机制作答，而不是只给术语列表。完整答案至少要说明：解释 std::remove 不真正删除元素，而是将"保留"元素移到前部、返回新逻辑尾迭代器；指出之后必须配合容器的 erase 才能真正缩短容器（erase-remove 惯用法）；给出代码示例 `v.erase(std::remove(v.begin(),v.end(),x), v.end());`；提到 C++20 引入 std::erase / erase_if 简化此惯用法。常见误区是只描述表面用法，漏掉前置条件、生命周期或性能/安全影响。评分时应看解释是否能指导实际写代码和排查错误。
