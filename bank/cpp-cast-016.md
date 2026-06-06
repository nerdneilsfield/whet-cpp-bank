---
qid: cpp-cast-016
type: single
kp: [cpp-casting]
difficulty: easy
answer_key: B
---

# 隐式 int→double 转换

```cpp
int a = 5, b = 2;
double result = a / b;
```

`result` 的值是？

A. `2.5`
B. `2.0`
C. `2`（int）
D. 编译错误

## 解析

正确答案是 B。表达式 `a / b` 中两个操作数都是 `int`，所以先执行整数除法，结果为 `2`；之后再转换成 `double` 存入 `result`，得到 `2.0`。若想得到 `2.5`，需让至少一个操作数先转为 `double`。
