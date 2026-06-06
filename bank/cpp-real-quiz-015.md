---
qid: cpp-real-quiz-015
type: single
kp: [cpp-cpp11, cpp-types]
primary_kp: cpp-cpp11
difficulty: hard
answer_key: B
tags: [interview-real, cppquiz, language-lawyer]
---
根据 C++17 标准，以下程序中各个 decltype 的类型是？

```cpp
int x = 0;
decltype(x)   a = 1;       // T1
decltype((x)) b = x;       // T2
```

下面对 `T1` 和 `T2` 的描述哪个正确？

A. `T1 = int`，`T2 = int`
B. `T1 = int`，`T2 = int&`
C. `T1 = int&`，`T2 = int&`
D. `T2` 编译错误（必须立即初始化）

---

**解析：**

[dcl.type.simple]：`decltype(entity)` 当 entity 是**未加括号的 id-expression** 时，结果就是该实体的**声明类型**。`x` 声明为 `int`，所以 `T1 = int`。

**加括号** `(x)` 后不再是 id-expression，被视为表达式。规则改为：表达式的值类别决定结果——`x` 是 lvalue，所以 `T2 = int&`（左值的 decltype 为 T&）；如果是 xvalue 则为 T&&，prvalue 则为 T。

这就是 `decltype(x)` vs `decltype((x))` 的著名"括号陷阱"。`T2 = int&` 必须初始化，`b = x` 合法。

**来源：** cppquiz.org（多题考点）；C++17 [dcl.type.simple]/4

## Explanation

正确答案是 B。
[dcl.type.simple]：decltype(entity) 当 entity 是未加括号的 id-expression 时，结果就是该实体的声明类型；x 声明为 int，所以 T1 = int。
加括号 (x) 后不再是 id-expression，被视为表达式；规则改为：表达式的值类别决定结果——x 是 lvalue，所以 T2 = int&（左值的 decltype 为 T&）；如果是 xvalue 则为 T&&，prvalue 则为 T。
这就是 decltype(x) vs decltype((x)) 的著名"括号陷阱"。
