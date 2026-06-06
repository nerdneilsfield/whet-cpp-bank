---
qid: cpp-scope-017
type: fill
kp: [cpp-scope-linkage]
difficulty: easy
answer_key: "未定义行为（UB）"
---

# 全局变量跨编译单元初始化顺序

有如下两个文件：

```cpp
// a.cpp
int A = 10;

// b.cpp
extern int A;
int B = A + 1;  // 依赖 A 的初始值
```

将两个文件编译链接成一个程序。`B` 的初始值是否**保证**为 11？

答：______ （填"保证"或"未定义行为（UB）"）

> 提示：C++ 标准不保证不同翻译单元中全局变量的初始化顺序。
