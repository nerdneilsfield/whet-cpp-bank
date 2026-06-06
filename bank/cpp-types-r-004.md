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
