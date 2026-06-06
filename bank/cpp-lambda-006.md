---
qid: cpp-lambda-006
type: single
kp: [cpp-lambdas]
difficulty: easy
answer_key: B
---

# Lambda 返回类型推导

```cpp
auto f = [](int x, int y) { return x + y; };
```

关于上述 lambda 的返回类型，说法正确的是？

A. 编译报错，lambda 必须显式指定返回类型
B. 返回类型由 `return` 语句自动推导为 `int`
C. 返回类型推导为 `auto`，运行时确定
D. 返回类型固定为 `double`，因为 `+` 运算符总返回 `double`

## 解析

正确答案是 B，对应“返回类型由 return 语句自动推导为 int”。本题考查 lambda 的捕获方式、调用对象和可变性，关键是区分按值捕获、按引用捕获以及闭包对象保存状态的规则。其他选项容易混淆相关概念：A 项“编译报错，lambda 必须显式指定返回类型”不满足题干要求；C 项“返回类型推导为 auto，运行时确定”不满足题干要求；D 项“返回类型固定为 double，因为 + 运算符总返回 double”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
