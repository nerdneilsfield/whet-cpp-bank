---
qid: cpp-mod-multi-med-007
type: multi
kp: [cpp-lambdas]
difficulty: medium
answer_key: [A, B, C]
---
关于 C++ lambda 表达式的性质，**哪些说法是正确的**？（多选）

```cpp
int x = 10;
auto f1 = [=]() { return x; };
auto f2 = [&]() mutable { ++x; };
auto f3 = [](auto a, auto b) { return a + b; };
auto f4 = [](int a) { return a * 2; };
```

A. `f1` 默认按值捕获，闭包内部 `x` 是一份拷贝，外部修改 `x` 不影响 `f1()` 的返回值
B. `mutable` 关键字仅去除**按值捕获成员**的 `const` 限定，不影响按引用捕获的修改能力
C. `f3` 是泛型 lambda（C++14），等价于带模板 `operator()` 的匿名类
D. `f4` 是无捕获 lambda，可以隐式转换为函数指针；`f1`/`f2` 因为有捕获也可以转换为函数指针

---

**解析：**

A 正确：`[=]` 按值捕获在闭包构造时复制 `x`，闭包持有副本，外部 `x` 后续改变不影响 `f1()`。
B 正确：按引用捕获 `[&]` 本身就能修改原对象；`mutable` 仅放开按值捕获副本的修改权，不影响 `[&]`。
C 正确：泛型 lambda 在 C++14 引入，闭包类型的 `operator()` 是函数模板。
D 错误：**只有无捕获**的 lambda 才能隐式转换为对应签名的函数指针；有捕获的 lambda 无法转换，因为函数指针无法承载状态。

## Explanation

正确答案是 [A, B, C]。A 正确：`[=]` 按值捕获在闭包构造时复制 `x`，闭包持有副本，外部 `x` 后续改变不影响 `f1()`。
A 正确：`[=]` 按值捕获在闭包构造时复制 `x`，闭包持有副本，外部 `x` 后续改变不影响 `f1()`。
D 错误：只有无捕获的 lambda 才能隐式转换为对应签名的函数指针；有捕获的 lambda 无法转换，因为函数指针无法承载状态。
