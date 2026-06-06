---
qid: cpp-iv-vtable-007
type: short
kp: [cpp-interview]
difficulty: medium
tags: [阿里, 字节跳动]
rubric:
  - 知道 override 的作用：显式声明覆盖，编译期检查签名匹配
  - 知道 final 可用于类（禁止继承）和虚函数（禁止进一步覆盖）
  - 理解 override 防止的典型错误：签名写错导致"新建函数"而非"覆盖"
  - 了解 final 的性能影响：编译器可去虚化（devirtualization）
  - 能给出实际代码示例
---

# override 和 final 关键字的作用？

## 问题

C++11 引入了 `override` 和 `final` 关键字，请分别说明它们的作用，以及不使用它们可能带来什么问题。

## 参考答案

### override

`override` 用于虚函数声明，告诉编译器"这个函数意图覆盖基类的虚函数"。编译器会检查：
1. 基类中是否存在同名虚函数；
2. 函数签名（参数类型、const 修饰、返回类型）是否完全匹配。

**不用 override 时的典型陷阱：**

```cpp
struct Base {
    virtual void process(int x) const;
};

struct Derived : Base {
    // 程序员想覆盖，但漏了 const
    void process(int x) { ... }  // 编译通过！但这是新函数，不是覆盖
};
// Base* p = new Derived();
// p->process(1);  → 调用 Base::process，不是 Derived::process，行为出乎意料
```

**用 override 后编译器立刻报错：**

```cpp
struct Derived : Base {
    void process(int x) override { ... }
    // error: 'process' marked 'override' but does not override any member function
    // 因为缺少 const，不匹配 Base::process(int) const
};
```

正确写法：

```cpp
struct Derived : Base {
    void process(int x) const override { ... }  // OK，签名完全匹配
};
```

### final

`final` 有两种用法：

**1. 用于类：禁止该类被继承**

```cpp
struct Leaf final : Base {
    void process(int x) const override { ... }
};

struct SubLeaf : Leaf { };  // error：cannot derive from 'final' base class 'Leaf'
```

**2. 用于虚函数：禁止派生类再覆盖**

```cpp
struct Mid : Base {
    void process(int x) const override final { ... }
};

struct Derived : Mid {
    void process(int x) const override { ... }  // error：overriding final function
};
```

### final 的性能意义：去虚化（devirtualization）

这是面试加分点。当编译器（或 JIT）能确定某个虚函数调用的目标类型是 `final` 类时，可以将间接的 vtable 查找优化为直接调用（inline 甚至消除调用），消除虚函数的分派开销：

```cpp
void call(Leaf& obj) {
    obj.process(1);  // 编译器知道 Leaf 是 final，
                     // 直接生成 Leaf::process 的直接调用，无需查 vtable
}
```

即使没有显式 `final`，现代编译器也会做"推测式去虚化"（speculative devirtualization），但 `final` 是给编译器的确定性提示，效果更强。

### 最佳实践

| 场景 | 建议 |
|------|------|
| 所有覆盖虚函数的地方 | 加 `override` |
| 不打算被继续派生的叶子类 | 加 `final`（有性能收益） |
| 某个虚函数不允许进一步定制 | 在函数声明加 `final` |
| 基类虚函数声明处 | 不需要 `override`，只加 `virtual` |
