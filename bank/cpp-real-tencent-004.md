---
qid: cpp-real-tencent-004
type: single
kp: [cpp-type-sizes, cpp-classes]
primary_kp: cpp-type-sizes
difficulty: medium
answer_key: B
tags: [interview-real, tencent]
---
```cpp
struct A {
    char c;       // 1 字节
    int  i;       // 4 字节
    short s;      // 2 字节
};
struct B {
    char c;
    short s;
    int  i;
};
```
在大多数 64 位平台上，sizeof(A) 和 sizeof(B) 分别是多少？

A. 7, 7
B. 12, 8
C. 12, 12
D. 8, 8

---

**解析：**

选 B。内存对齐规则：
1. **每个成员**对齐到 `min(自身大小, #pragma pack 值)` 的倍数偏移
2. **结构体整体**对齐到最大成员对齐值的倍数（用于数组中正确对齐）

**A 的布局：**
```
[c (1)] [pad (3)] [i (4)] [s (2)] [pad (2)]
偏移:    0       4       8     10
结构体对齐: 4，总大小 = 12
```
c 在偏移 0；i 要对齐到 4 的倍数 → 偏移 4，填充 3；s 在偏移 8（任意 2 的倍数都行）；最后整体对齐到 4，填充 2 → **12**。

**B 的布局：**
```
[c (1)] [pad (1)] [s (2)] [i (4)]
偏移:   0       2       4
结构体对齐: 4，总大小 = 8
```
c 在偏移 0；s 要对齐到 2 → 偏移 2，填充 1；i 要对齐到 4 → 偏移 4；总大小 8，恰好是 4 的倍数 → **8**。

**结论：** 把成员按大小**降序排列**（或合理排列），可以减少 padding 浪费。这是底层数据结构优化常见技巧。

`alignof(A) == alignof(B) == 4`，`alignof(int) == 4`。

**来源：** 腾讯 C++ 后端面试（参考：cppreference、《深入理解计算机系统》）

## Explanation

正确答案是 B。
选 B；内存对齐规则： 每个成员对齐到 min(自身大小, #pragma pack 值) 的倍数偏移 结构体整体对齐到最大成员对齐值的倍数（用于数组中正确对齐） A 的布局： c 在偏移 0；i 要对齐到 4 的倍数 → 偏移 4，填充 3；s 在偏移 8（任意 2 的倍数都行）；最后整体对齐到 4，填充 2 → 12。
B 的布局： c 在偏移 0；s 要对齐到 2 → 偏移 2，填充 1；i 要对齐到 4 → 偏移 4；总大小 8，恰好是 4 的倍数 → 8；结论： 把成员按大小降序排列（或合理排列），可以减少 padding 浪费。
