---
qid: cpp-tmp-med-013
type: single
kp: [cpp-templates]
difficulty: medium
answer_key: C
---

`std::advance` 在标准库内部使用 tag dispatch 区分迭代器类别。对于**随机访问迭代器**（random access iterator），`advance(it, n)` 的实现是？

A. 循环调用 `++it` 共 n 次，O(n)
B. 调用虚函数 `it.advance(n)`，运行期分派
C. 直接执行 `it += n`，O(1)
D. 调用 `std::distance` 再重新计算位置

---

**解析：**

`std::advance` 利用 tag dispatch（或 C++17 中的 `if constexpr`）区分迭代器类别：

- **input/forward/bidirectional iterator**：只能 `++it`（或 `--it`），O(n)。
- **random access iterator**（如 `vector::iterator`）：支持 `it += n`，O(1)。

tag 来自 `std::iterator_traits<It>::iterator_category`，如 `std::random_access_iterator_tag`。编译期选择正确的重载，避免对随机访问迭代器做不必要的循环。
