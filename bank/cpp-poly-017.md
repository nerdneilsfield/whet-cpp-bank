---
qid: cpp-poly-017
type: single
kp: [cpp-polymorphism]
difficulty: easy
answer_key: B
---

# 以下代码能否编译通过？

```cpp
struct Base {
    virtual void g() final;
};
struct Derived : Base {
    void g() override;   // 尝试重写被 final 修饰的函数
};
```

A. 可以编译，`final` 只是注释性标记  
B. 编译错误：`Base::g()` 已声明 `final`，`Derived` 不能重写  
C. 可以编译，但运行时会调用 `Base::g()`  
D. 编译错误：`final` 和 `override` 不能同时使用

## Explanation

正确答案是 B，因为该选项对应 `编译错误：`Base::g()` 已声明 `final`，`Derived` 不能重写`，符合题中代码或概念的 C++ 语义。多态题的关键是区分静态类型与动态类型：只有通过基类指针或引用调用虚函数时，才会发生运行期动态分派。常见误区是把普通成员函数、对象切片、构造/析构期调用也当成完整的虚调用场景。 A 项、C 项、D 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
