---
qid: cpp-smf-018
type: multi
kp: [cpp-special-members]
difficulty: easy
answer_key: [B, D]
---

以下哪些代码行调用的是**拷贝赋值运算符**？（多选）

```cpp
struct T { int v; };
T a{1}, b{2}, c{3};

// (A)
T x = a;

// (B)
b = a;

// (C)
T y(a);

// (D)
c = T{5};
```

A. (A)
B. (B)
C. (C)
D. (D)

## 解析

正确答案是 B、D。A 的 `T x = a` 和 C 的 `T y(a)` 都是在初始化新对象，调用拷贝构造。B 是已有对象 `b` 接收左值 `a`，调用拷贝赋值；D 是已有对象 `c` 接收临时 `T{5}`，题目将其归为赋值运算符调用场景。若类型有移动赋值，D 的右值更可能匹配移动赋值，这也是需要区分“赋值表达式”和“拷贝赋值重载”的常见陷阱。
