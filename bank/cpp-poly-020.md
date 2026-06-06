---
qid: cpp-poly-020
type: multi
kp: [cpp-polymorphism]
difficulty: easy
answer_key: [B, C, E]
---

# 以下哪些说法是正确的？（多选）

```cpp
struct Foo final {
    virtual void bar();
};
```

A. `Foo` 可以被继承，`final` 只禁止重写 `bar`  
B. `Foo` 不能被任何类继承，尝试继承会编译报错  
C. `Foo` 的对象仍然可以正常创建  
D. `Foo::bar()` 因为在 `final` 类中，所以不需要 `virtual`  
E. `final` 修饰类时写在类名之后、`{` 之前，形如 `struct Foo final { ... };`
