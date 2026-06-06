---
qid: cpp-oop-multi-med-002
type: multi
kp: [cpp-polymorphism]
difficulty: medium
answer_key: [A, B, D]
---
关于 C++11 的 `override` 和 `final` 关键字，**哪些说法是正确的**？（多选）

```cpp
struct Base { virtual void f(int) const; };
struct D1 : Base {
    void f(int) override;          // (1)
    void f(double) override;       // (2)
};
struct D2 : Base {
    void f(int) const final;       // (3)
};
struct D3 : D2 {
    void f(int) const override;    // (4)
};
```

A. (1) 编译错误：`Base::f` 是 `const`，`D1::f` 未加 `const`，签名不一致，`override` 检查失败
B. (2) 编译错误：`Base` 中无 `f(double)`，没有可重写的虚函数
C. `final` 用于成员函数时只能修饰**虚函数**，并且能继续被派生类隐藏（隐藏不算重写）
D. (4) 编译错误：`D2::f` 是 `final`，禁止 `D3` 重写

---

**解析：**

A 正确：`override` 强制要求签名（包含 `const`、引用限定、参数类型）完全匹配基类虚函数，否则编译失败。这是它的核心价值——防止"以为重写实际未重写"的 bug。
B 正确：`f(double)` 不存在于 `Base`，`override` 检查失败。如果去掉 `override`，则只是声明了新函数（与基类的 `f(int)` 共存为重载/隐藏关系）。
C 错误：`final` 同样只能用于虚函数，且**禁止派生类重写**该虚函数，不存在"隐藏不算"的豁免——一旦 `D3` 声明同签名虚函数即编译错误。
D 正确：与 C 中分析一致，`final` 的目的就是关闭后续重写。

## Explanation

A、B、D 正确：`override` 会严格检查参数、cv 限定和引用限定等签名是否真的覆盖基类虚函数。`final` 用在虚函数上会禁止派生类继续覆盖同一虚函数。常见误区是去掉 `override` 后代码仍能编译就说明覆盖成功；实际上可能只是声明了隐藏或重载的新函数。
