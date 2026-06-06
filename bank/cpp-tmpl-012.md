---
qid: cpp-tmpl-012
type: single
kp: [cpp-templates]
difficulty: easy
answer_key: D
---

# 编译错误判断

```cpp
template<typename T>
void print(T val) {
    std::cout << val << std::endl;
}

print("hello");
print(42);
print(3.14);
```

下列说法正确的是？

A. 三次调用都会编译错误，因为类型不同
B. 只有 `print("hello")` 会编译错误
C. 只有 `print(3.14)` 会编译错误
D. 三次调用都能正确编译，T 分别推导为 `const char*`、`int`、`double`

## 解析

正确答案是 D，即 三次调用都能正确编译，T 分别推导为 `const char*`、`int`、`double`。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、C 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。模板题要区分编译期实例化、类型推导、特化/重载匹配和 SFINAE/约束；不要把模板当作运行时多态。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
