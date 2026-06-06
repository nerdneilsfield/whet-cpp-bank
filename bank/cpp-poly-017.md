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
