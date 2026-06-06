---
qid: cpp-friend-med-002
type: single
kp: [cpp-friend]
difficulty: medium
answer_key: D
---

在类内部定义友元函数时，该函数具有特殊隐式属性。以下代码输出是？

```cpp
#include <iostream>

struct Widget {
    friend void hello() { std::cout << "Hello\n"; }
    void call() { hello(); }
};

int main() {
    Widget w;
    w.call();
}
```

A. 输出 `Hello`
B. 编译失败，因为友元函数定义在类内但缺少外部声明
C. 输出空，因为友元函数定义时不生成代码
D. 链接失败（undefined reference to `hello()`）

---

**解析：**

类内定义的友元函数**不是**该类的成员函数，它在外围命名空间的作用域中，但**只能通过 ADL（Argument-Dependent Lookup）找到**。因为 `hello()` 的参数类型是 `void`，没有任何参数可以触发 ADL，而普通的非限定名字查找找不到它。

`Widget::call()` 中的 `hello()` 调用：名字查找会先看外围作用域——没有找到（因为类内定义的友元函数不在普通查找的表里，只有 ADL 能找到它）。ADL 的前提是有参数，但 `hello()` 无参，所以无法触发 ADL。结果是链接失败。

修复方式：在类外再提供一个声明 `void hello();`，或在全局作用域声明该函数。这个特性的意外之处常导致"类内定义友元函数却无法被直接调用"。

## 解析

正确答案是 D，对应“链接失败（undefined reference to hello()）”。本题考查友元声明的访问权限规则，关键是友元只授予特定函数或类访问权，不会自动成为成员。其他选项容易混淆相关概念：A 项“输出 Hello”不满足题干要求；B 项“编译失败，因为友元函数定义在类内但缺少外部声明”不满足题干要求；C 项“输出空，因为友元函数定义时不生成代码”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
