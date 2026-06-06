---
qid: cpp-inh-hard-003
type: single
kp: [cpp-inheritance]
difficulty: hard
answer_key: A
---

考虑以下代码，关于派生类对象间赋值的潜在问题：

```cpp
struct Base { int b; virtual ~Base() = default; };
struct Derived : Base { int d; };

void copy(Base& dst, const Base& src) {
    dst = src;  // ①
}

Derived d1{ {1}, 2 }, d2{ {3}, 4 };
copy(d1, d2);
```

执行 `copy(d1, d2)` 后，`d1.d` 的值是？

A. `2`（未变），因为编译器合成的 `Base::operator=` 只复制 `Base` 子对象，发生了"赋值切片"
B. `4`，因为通过引用调用会动态分派
C. 未定义行为，应当返回 `4` 但实现相关
D. 编译错误，因为 `Base::operator=` 已被 `virtual ~Base()` 隐式删除

## Explanation

这是**赋值切片（assignment slicing）**。`dst = src` 在 `Base&` 上调用，名字查找绑定到 `Base::operator=`（默认合成）——拷贝赋值运算符**不是**虚函数（即使设为虚，签名也会因协变问题难以匹配派生类），所以只复制 `Base` 子对象 `b`，`d1.d` 保持 `2`。D 错：虚析构不会删除合成赋值；B 错：拷贝赋值默认非虚。要在多态层次中安全赋值，常见模式是禁止 `Base` 的拷贝赋值（`= delete`）并提供 `virtual clone()`/`virtual assign()` 等显式接口。
