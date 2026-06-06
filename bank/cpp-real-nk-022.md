---
qid: cpp-real-nk-022
type: single
kp: [cpp-type-sizes]
primary_kp: cpp-type-sizes
difficulty: medium
answer_key: B
tags: [interview-real, alibaba]
---

```cpp
struct A {
    char c;     // 1 byte
    int i;      // 4 bytes
    char d;     // 1 byte
};

struct B {
    char c;     // 1 byte
    char d;     // 1 byte
    int i;      // 4 bytes
};
```

在 64 位 Linux 默认对齐下，`sizeof(A)` 和 `sizeof(B)` 分别是：

A. `A=6, B=6`
B. `A=12, B=8`
C. `A=8, B=8`
D. `A=12, B=12`

---

**解析：**

内存对齐规则：
1. 每个成员从其自然对齐边界开始（int 对齐到 4 字节）
2. 结构体整体对齐到最大成员对齐
3. 末尾填充使总大小是对齐的整数倍

**A 的布局**：
```
偏移 0:  char c       (1 byte)
偏移 1-3: padding     (3 bytes)
偏移 4-7: int i       (4 bytes)
偏移 8:  char d       (1 byte)
偏移 9-11: padding    (3 bytes，整体对齐到 4)
```
sizeof(A) = 12

**B 的布局**：
```
偏移 0:  char c       (1 byte)
偏移 1:  char d       (1 byte)
偏移 2-3: padding     (2 bytes)
偏移 4-7: int i       (4 bytes)
```
sizeof(B) = 8

经验：**按大小降序排列成员**可减小结构体大小，对大型对象数组、网络数据包结构尤其重要。

**来源：** 网易/阿里 C++ 内存对齐面试题 / CSDN 八股

## Explanation

正确答案是 B。
内存对齐规则： 每个成员从其自然对齐边界开始（int 对齐到 4 字节） 结构体整体对齐到最大成员对齐 末尾填充使总大小是对齐的整数倍 *A 的布局： sizeof(A) = 12 *B 的布局： sizeof(B) = 8 经验：按大小降序排列成员可减小结构体大小，对大型对象数组、网络数据包结构尤其重要。
