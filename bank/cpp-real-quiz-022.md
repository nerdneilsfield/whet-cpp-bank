---
qid: cpp-real-quiz-022
type: single
kp: [cpp-lambdas]
primary_kp: cpp-lambdas
difficulty: hard
answer_key: C
tags: [interview-real, cppquiz, language-lawyer]
---
根据 C++17 标准，以下程序的行为是？

```cpp
#include <iostream>
int main() {
    int x = 10;
    auto f = [x]() { x = 42; return x; };
    std::cout << f();
}
```

A. 输出 `42`
B. 输出 `10`
C. 编译错误
D. 行为未定义

---

**解析：**

[expr.prim.lambda.closure]：lambda 默认生成的 `operator()` 是 **const** 成员函数。`[x]` 按值捕获 `x` 为闭包类的数据成员，在 const 成员函数内**不能修改非 mutable 成员** → 编译错误：

```
error: assignment of read-only variable 'x'
note: in 'operator()' of '[x]() {...}', which is 'const'
```

修正方法：
1. `[x]() mutable { x = 42; return x; }` —— 关掉 const
2. 通过引用捕获：`[&x]() { x = 42; return x; }`

注意：即使是 mutable lambda，修改的也只是闭包内部的副本，外层的 x 并不会变。

**来源：** C++ Brain Teasers；C++17 [expr.prim.lambda.closure]/4

## Explanation

正确答案是 C。
[expr.prim.lambda.closure]：lambda 默认生成的 operator() 是 const 成员函数。[x] 按值捕获 x 为闭包类的数据成员，在 const 成员函数内不能修改非 mutable 成员 → 编译错误： 修正方法： [x]() mutable { x = 42; return x; } —— 关掉 const 通过引用捕获：[&x]() { x = 42; return x; } 注意：即使是 mutable lambda，修改的也只是闭包内部的副本，外层的 x 并不会变。
