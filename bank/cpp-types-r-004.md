---
qid: cpp-types-r-004
type: single
kp: [cpp-types]
difficulty: easy
answer_key: B
---

# 代码阅读：`const int*` vs `int* const` 写操作

```cpp
int val = 10;
const int* p = &val;
int* const q = &val;
```

下列哪个操作**合法**？

A. `p = nullptr;` 然后 `*p = 5;`（解引用空指针）  
B. `*q = 99;`（通过顶层-const 指针写入所指对象）  
C. `*p = 20;`（通过底层-const 指针写入所指对象）  
D. `q = nullptr;`（修改 const 指针本身）

## Explanation

正确答案是 B，即 `*q = 99;`（通过顶层-const 指针写入所指对象）。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。指针、数组和引用题要注意数组到指针退化、指针算术按元素大小推进，以及引用绑定后只是对象别名。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
