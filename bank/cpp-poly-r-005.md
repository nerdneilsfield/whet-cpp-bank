---
qid: cpp-poly-r-005
type: single
kp: [cpp-polymorphism]
difficulty: easy
answer_key: "C"
---

## 题目

以下代码能否通过编译？

```cpp
struct Base {
    virtual void run() final { }
};

struct Mid : Base {
    void run() override { }   // (1)
};

int main() { }
```

A. 能编译，输出为空
B. 能编译，但运行时崩溃
C. 编译错误，`run()` 被 `final` 禁止重写
D. 链接错误

## 解析

`Base::run()` 被标记为 `final`，表示该虚函数在此层级之后**不得再被重写**。`Mid::run()` 试图重写它，编译器直接报错：`overriding final function 'virtual void Base::run()'`。`final` 既可修饰整个类（禁止继承），也可修饰单个虚函数（禁止进一步重写）。
