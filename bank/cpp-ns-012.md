---
qid: cpp-ns-012
type: single
kp: [cpp-preprocessor]
difficulty: easy
answer_key: C
---

为什么不建议在头文件中写 `using namespace std;`？

A. 头文件不支持 `using` 语法
B. `std` 命名空间在头文件中不可用
C. 会污染所有包含该头文件的编译单元的命名空间，可能引发名称冲突
D. 会导致循环包含
