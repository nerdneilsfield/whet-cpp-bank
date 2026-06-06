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
