---
qid: cpp-poly-015
type: single
kp: [cpp-polymorphism]
difficulty: easy
answer_key: A
---

# 阅读代码，`override` 标记是否会触发编译错误？

```cpp
struct Base {
    virtual void foo(int x);
};
struct Derived : Base {
    void foo(double x) override;   // 注意参数类型不同
};
```

A. 编译错误：`foo(double)` 与基类 `foo(int)` 签名不匹配，`override` 检测到错误  
B. 编译通过：`override` 只是提示，不影响编译  
C. 编译通过：`Derived::foo(double)` 是合法的重载  
D. 编译通过，但运行时会绑定到 `Base::foo(int)`

## Explanation

正确答案是 A，因为该选项对应 `编译错误：`foo(double)` 与基类 `foo(int)` 签名不匹配，`override` 检测到错误`，符合题中代码或概念的 C++ 语义。多态题的关键是区分静态类型与动态类型：只有通过基类指针或引用调用虚函数时，才会发生运行期动态分派。常见误区是把普通成员函数、对象切片、构造/析构期调用也当成完整的虚调用场景。 B 项、C 项、D 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
