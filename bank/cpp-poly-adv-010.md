---
qid: cpp-poly-adv-010
type: single
kp: [cpp-polymorphism]
difficulty: medium
answer_key: B
---

关于 `std::any` 的内部实现，下列说法**正确**的是？

```cpp
#include <any>
#include <iostream>

int main() {
    std::any a = 42;         // 存储 int
    std::any b = std::string(200, 'x');  // 存储较大字符串

    // a 的存储位置 vs b 的存储位置？
}
```

A. `a` 和 `b` 都在堆上分配，`std::any` 永远通过 `new` 存储值
B. `a` 可能存储在 `std::any` 对象内部的栈缓冲区（SBO），`b` 因为太大会堆分配
C. `a` 和 `b` 都存储在 `std::any` 内部，因为 `std::any` 的大小是无限的
D. `std::any` 使用 `union` 存储所有类型，无论大小都不堆分配

---

**解析：**

`std::any` 的典型实现采用**小对象优化（Small Buffer Optimization, SBO）**：

- 对象内部有一个固定大小的内联缓冲区（通常 16~24 字节，实现定义）。
- 若存储的类型大小 ≤ 缓冲区且对齐满足要求，对象直接存在缓冲区中（**无堆分配**）。
- 若存储的类型过大或对齐不满足，则退化为 `new` 堆分配。

对于 `int`（4 字节）：触发 SBO，存在栈缓冲区。
对于 `std::string(200, 'x')`：`std::string` 对象本身通常 24~32 字节，可能超出 SBO 阈值，或本身内部已有堆分配。

这与 `std::function` 的 SBO 逻辑类似，都是为了避免频繁堆分配的小值优化。
