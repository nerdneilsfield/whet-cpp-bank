---
qid: cpp-tmp-hard-012
type: multi
kp: [cpp-templates]
difficulty: hard
answer_key: [B, D]
---

比较以下两种存储"可调用对象"的方式：

```cpp
// 方式 A：虚函数（继承方式）
struct Base { virtual void call() = 0; };
struct Impl : Base {
    void call() override { std::cout << "impl\n"; }
};

// 方式 B：类型擦除（std::function）
std::function<void()> f;
f = []() { std::cout << "lambda\n"; };
```

以下哪些说法正确？（多选）

A. 方式 A 可以直接存储 lambda，无需继承
B. 方式 B（`std::function`）可以存储任意可调用对象，包括 lambda、函数指针、仿函数
C. 方式 A 和方式 B 在运行时开销上完全相同
D. 方式 B 的类型擦除技术使调用者无需知道具体类型，方式 A 需要共同基类

## Explanation

正确选项是 B（方式 B（`std::function`）可以存储任意可调用对象，包括 lambda、函数指针、仿函数）、D（方式 B 的类型擦除技术使调用者无需知道具体类型，方式 A 需要共同基类），它们符合本题涉及的 C++ 规则。A（方式 A 可以直接存储 lambda，无需继承）、C（方式 A 和方式 B 在运行时开销上完全相同） 的关键问题在于混淆了相关概念或把实现细节当成语言保证。指针、数组和引用题要注意数组到指针退化、指针算术按元素大小推进，以及引用绑定后只是对象别名。 多选题要逐项判断，不能因为某个说法在常见平台上成立就认为它是标准规则。
