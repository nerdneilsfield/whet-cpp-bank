---
qid: cpp-smf-013
type: single
kp: [cpp-special-members]
difficulty: easy
answer_key: D
---

以下代码能否编译通过？原因是什么？

```cpp
struct NoCopy {
    NoCopy() = default;
    NoCopy(const NoCopy&) = delete;
};

NoCopy a;
NoCopy b = a;  // 此行
```

A. 能编译，调用移动构造
B. 能编译，调用默认构造
C. 能编译，调用拷贝赋值运算符
D. 不能编译，拷贝构造已被 `= delete` 禁用

## Explanation

正确答案是 D，`NoCopy b = a;` 需要用左值 `a` 拷贝初始化新对象，因此会选择拷贝构造函数。该拷贝构造函数被 `= delete` 显式删除，所以调用点编译错误。默认构造和移动构造都不能替代这个从左值复制的操作。 这类题的关键是区分语法形式、对象生命周期和所有权语义：语法看似相近时，应先判断谁拥有资源、表达式值类别是什么，以及标准是否保证该行为；不要根据实现习惯或表面写法推断答案。
