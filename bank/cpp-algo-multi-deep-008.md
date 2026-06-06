---
qid: cpp-algo-multi-deep-008
type: multi
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: [A, B, D]
---

关于 C++20 ranges 的优势，下列哪些**正确**？（多选）

```cpp
auto r = v | std::views::filter(odd) | std::views::transform(square);
```

A. 视图（views）**惰性求值**，不产生中间容器
B. ranges 算法支持**投影**（projection）参数，可在比较前映射元素
C. ranges 算法不能用于普通迭代器对，只能用于 view
D. 对临时容器调用返回迭代器的算法会得到 `std::ranges::dangling`，把潜在 UB 提前为编译期错误

---

**解析：**

- A ✅：视图惰性、零拷贝；典型管道无堆分配。
- B ✅：投影把"取键"逻辑从比较器分离出来，代码更清晰。
- C ❌：ranges 算法既接受 range 对象也接受 `(begin, end)` 迭代器对。
- D ✅：dangling 检查通过类型系统拒绝悬挂迭代器使用。

注意 `filter_view::iterator` 是 ForwardIterator（不是 RandomAccess），所以管道末端常常退化为前向遍历，无法直接 `sort`。
