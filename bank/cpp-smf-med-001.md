---
qid: cpp-smf-med-001
type: single
kp: [cpp-special-members]
difficulty: medium
answer_key: C
---

下列类 `Buf` 显式定义了析构函数和拷贝控制，但没有声明移动构造/移动赋值。`f()` 中第二行的行为是？

```cpp
struct Buf {
    int* p;
    Buf(std::size_t n) : p(new int[n]) {}
    ~Buf()                       { delete[] p; }
    Buf(const Buf&  o);          // 深拷贝
    Buf& operator=(const Buf& o);// 深拷贝
};

Buf make();        // 返回一个 Buf 临时对象

void f() {
    Buf a = make();          // ①
    Buf b = std::move(a);    // ②  ← 关注这一行
}
```

A. 调用 `Buf` 的隐式生成的移动构造函数，`a.p` 被置空
B. 编译错误：因为 `Buf` 定义了拷贝控制，移动构造函数被隐式删除
C. 调用 `Buf` 的拷贝构造函数（深拷贝），`a.p` 保持原值
D. 调用 `Buf` 的拷贝构造函数，但 `a.p` 在 `std::move` 后被置空

---

**解析：**

“Rule of Five”/[class.copy.ctor] 规定：一旦用户显式声明了拷贝构造、拷贝赋值或析构函数中的任意一个，编译器**不会**再隐式生成移动构造和移动赋值。注意是“不生成”，不是“delete”——所以不会编译错。

当 `Buf b = std::move(a)` 进行重载决议时，找不到移动构造函数，但 `std::move(a)` 产生的右值能绑定到 `const Buf&`，于是回退到拷贝构造函数。`std::move` 本身只做类型转换（变成 xvalue），并不修改 `a`，所以 `a.p` 仍指向原数组。

最终结果：发生了深拷贝（浪费了移动语义的性能优化），但程序行为正确，没有 UB。修复方法是显式 `=default` 或自己实现移动构造与移动赋值（Rule of Five）。
