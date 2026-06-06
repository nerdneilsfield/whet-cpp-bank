---
qid: cpp-lambda-med-001
type: single
kp: [cpp-lambdas]
difficulty: medium
answer_key: C
---
下列代码在 `main` 中调用 `f()` 时会发生什么？

```cpp
#include <functional>
std::function<int()> make() {
    int x = 42;
    return [&]() { return x; };
}
int main() {
    auto f = make();
    return f();
}
```

A. 总是返回 42
B. 编译错误
C. 未定义行为：lambda 捕获了已离开作用域的 `x`
D. 自动延长 `x` 的生命周期

---

**解析：**

`[&]` 是按引用捕获所有用到的外部变量。`x` 是 `make()` 内的局部变量，函数返回后 `x` 被销毁，lambda 内的引用变成悬垂引用。`f()` 在 `main` 中调用时读取 `x` 是 UB。C++ 引用从来不延长被引用对象的生命周期（除了字面量绑定到 `const T&` 的特殊规则，且仅限初始化点）。要安全地把局部变量带出，必须值捕获 `[=]` 或 `[x]`，或者用 `[x = std::move(x)]` 等初始化捕获显式转移所有权。
