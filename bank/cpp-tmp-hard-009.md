---
qid: cpp-tmp-hard-009
type: multi
kp: [cpp-templates]
difficulty: hard
answer_key: [A, C]
---

比较以下两种实现"对所有参数求和"的方式：

```cpp
// 方式 A：C++17 fold 表达式
template<typename... Args>
auto sum_fold(Args... args) {
    return (args + ...);
}

// 方式 B：递归可变参数模板（C++11）
template<typename T>
T sum_recursive(T t) { return t; }

template<typename T, typename... Rest>
T sum_recursive(T t, Rest... rest) {
    return t + sum_recursive(rest...);
}
```

以下哪些说法正确？（多选）

A. 方式 A 代码量更少，更简洁
B. 方式 B 比方式 A 运行效率更高
C. 方式 A 需要 C++17 支持，方式 B 在 C++11 即可使用
D. 两者均要求所有参数类型完全相同，不能混用 `int` 和 `double`

## Explanation

正确选项是 A（方式 A 代码量更少，更简洁）、C（方式 A 需要 C++17 支持，方式 B 在 C++11 即可使用），它们符合本题涉及的 C++ 规则。B（方式 B 比方式 A 运行效率更高）、D（两者均要求所有参数类型完全相同，不能混用 `int` 和 `double`） 的关键问题在于混淆了相关概念或把实现细节当成语言保证。模板题要区分编译期实例化、类型推导、特化/重载匹配和 SFINAE/约束；不要把模板当作运行时多态。 多选题要逐项判断，不能因为某个说法在常见平台上成立就认为它是标准规则。
