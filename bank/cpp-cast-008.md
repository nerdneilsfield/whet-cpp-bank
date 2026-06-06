---
qid: cpp-cast-008
type: single
kp: [cpp-casting]
difficulty: easy
answer_key: B
---

# 窄化转换与列表初始化

```cpp
double d = 3.7;
int a = d;        // 行 1
int b{d};         // 行 2
```

下列说法正确的是？

A. 行 1 和行 2 都能正常编译，结果相同
B. 行 1 合法（隐式截断），行 2 在标准 C++ 中产生编译错误/警告（窄化）
C. 行 2 合法，行 1 编译错误
D. 两行都是未定义行为
