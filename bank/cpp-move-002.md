---
qid: cpp-move-002
type: single
kp: [cpp-move-semantics]
difficulty: easy
answer_key: C
---

# 判断表达式的值类别

以下哪个表达式是 **rvalue**？

```cpp
int x = 5;
int arr[3] = {1, 2, 3};
```

A. `x`
B. `arr[0]`
C. `x + 1`
D. `arr`

## Explanation

正确答案是 C，`x + 1` 产生一个临时计算结果，是右值。`x` 是具名变量，是左值；`arr[0]` 表示数组元素，也可定位和赋值，是左值；`arr` 表达式在多数上下文会退化为指针，但数组表达式本身仍有对象身份。常见误区是把“在右边出现”当成右值判断依据。
