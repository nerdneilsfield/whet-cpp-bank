---
qid: cpp-size-med-002
type: single
kp: [cpp-type-sizes]
difficulty: medium
answer_key: B
---

C++ 中 `sizeof` 空类（empty class）的结果是？以下代码输出是：

```cpp
#include <iostream>

struct Empty {};

struct WithEmptyMember {
    Empty e;
    int x;
};

int main() {
    std::cout << sizeof(Empty) << " " << sizeof(WithEmptyMember);
}
```

A. `0 4`（Empty 的大小为 0，不占用空间）
B. `1 8`（Empty 的大小为 1，满足 C++ 对象唯一地址要求；WithEmptyMember 因对齐和填充占用 8 字节）
C. `1 4`（Empty 占 1 字节，但成员不会引入额外填充，因为 Empty 可以对齐到 1）
D. `0 4`（编译器做了空基类优化 EBO）

---

**解析：**

C++ 标准规定：**每个完整的对象（complete object）必须具有唯一地址且占用非零大小**。因此 `sizeof(Empty) == 1`（至少 1 字节），不能为 0。

对于 `WithEmptyMember`：
- `Empty e`：虽然 Empty"空"，但它作为一个数据成员（不是基类），必须占据 1 字节。
- 成员布局：`e` 占 [0, 1)，`int x` 要求 4 字节对齐，填充到偏移 4，`x` 占 [4, 8)。
- 总大小：8 字节。

注意：**空基类优化（EBO/EBCO）仅适用于基类**。如果 `struct WithEmptyBase : Empty`，则 `Empty` 基类子对象不占用空间，可能（取决于对齐）使 `sizeof(WithEmptyBase) == 4`。EBO 是标准库（如 `std::vector` 中的分配器）常见的优化手段。