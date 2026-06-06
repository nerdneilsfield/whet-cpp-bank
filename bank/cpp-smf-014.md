---
qid: cpp-smf-014
type: single
kp: [cpp-special-members]
difficulty: easy
answer_key: A
---

以下代码中，`Bar b2 = std::move(b1);` 调用的是哪个特殊成员函数？

```cpp
struct Bar {
    Bar() = default;
    Bar(const Bar&) = default;
    Bar(Bar&&) = default;
};
Bar b1;
Bar b2 = std::move(b1);
```

A. 移动构造函数
B. 拷贝构造函数
C. 拷贝赋值运算符
D. 默认构造函数

## 解析

正确答案是 A，`std::move(b1)` 将 `b1` 转成 xvalue，初始化新对象 `b2` 时移动构造函数是最佳匹配。这里类显式默认了 `Bar(Bar&&)`，因此可调用移动构造。注意 `std::move` 本身不搬移数据，只影响重载决议。 这类题的关键是区分语法形式、对象生命周期和所有权语义：语法看似相近时，应先判断谁拥有资源、表达式值类别是什么，以及标准是否保证该行为；不要根据实现习惯或表面写法推断答案。
