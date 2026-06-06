---
qid: cpp-tmpl-multi-hard-004
type: multi
kp: [cpp-templates]
difficulty: hard
answer_key: [A, C, D]
---
关于 C++17 fold expression 与可变参数模板的参数包展开，以下说法正确的是哪些？

```cpp
template<typename... Args>
auto sum(Args... args) {
    return (args + ...);          // (1) 一元右折叠
}

template<typename... Args>
void print(Args... args) {
    ((std::cout << args << ' '), ...);   // (2)
}
```

A. (1) 中 `(args + ...)` 等价于 `arg1 + (arg2 + (arg3 + ...))`，是右折叠；左折叠应写作 `(... + args)`。
B. 当参数包为空时，所有一元折叠（无初值）都有合法默认值，例如 `(args + ...)` 对空包返回 `0`。
C. (2) 利用了逗号运算符的折叠特性，对每个参数依次执行 `std::cout << args << ' '`，是参数包展开的常见技巧。
D. 参数包不能在任意位置随意"裸用"——必须出现在合法的展开上下文中（函数调用实参列表、初始化列表、模板实参列表、fold 表达式等），否则编译失败。

---

**解析：**

A 正确：一元右折叠 `(E op ...)` 展开为 `E1 op (E2 op (... op En))`，是右结合；左折叠 `(... op E)` 展开为 `((E1 op E2) op ...) op En`。
B 错误：一元折叠对空包通常是非法的，只有 `&&`（结果 `true`）、`||`（结果 `false`）、`,`（结果 `void()`）三种运算符的空包折叠有合法默认值，`+` 的空包折叠是错误。
C 正确：`((expr), ...)` 是逗号一元折叠，依次执行每个表达式，是 C++17 之前用初始化列表 trick 替代的标准写法。
D 正确：参数包扩展只能出现在标准列举的有限上下文中，例如 `f(args...)`、`{args...}`、`Foo<args...>`、`(args op ...)` 等，单独写 `args` 或在任意算术表达式中裸用都不合法。
