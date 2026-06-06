---
qid: cpp-fp-009
type: single
kp: [cpp-function-pointers]
difficulty: easy
answer_key: B
---

# 代码阅读：函数指针赋值与调用

```cpp
int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }

int (*fp)(int, int) = add;
fp = sub;
int result = fp(10, 3);
```

`result` 的值是？

A. 13  
B. 7  
C. 编译错误  
D. 未定义行为  
