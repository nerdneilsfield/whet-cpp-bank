---
qid: cpp-real-quiz-013
type: single
kp: [cpp-special-members, cpp-classes]
primary_kp: cpp-special-members
difficulty: hard
answer_key: C
tags: [interview-real, cppquiz, language-lawyer]
---
根据 C++17 标准，以下程序的行为是？

```cpp
struct S {
    const int x;
};
int main() {
    S s;        // 注意：没有初始化器
}
```

A. 通过，`s.x` 为 0
B. 通过，`s.x` 为不定值
C. 编译错误（默认构造函数被隐式 deleted）
D. 链接错误

---

**解析：**

[class.default.ctor]：如果类含有 **const 非静态数据成员**且没有 brace-or-equal initializer，编译器**隐式声明的默认构造函数是 deleted** 的——因为没法把一个 const 成员构造成"未初始化"状态。

`S s;` 是 default-initialization，会去找隐式默认构造函数，但它已被 deleted，**编译错误**：
```
error: use of deleted function 'S::S()'
note: 'S::S()' is implicitly deleted because the default definition would be ill-formed: uninitialized const member in 'struct S'
```

修复办法：
1. 写 `S s{42};`（聚合初始化）
2. 类内默认值：`const int x = 42;`
3. 显式提供构造函数

含引用成员的情况完全一样。

**来源：** C++ Brain Teasers；C++17 [class.default.ctor]/2.2
