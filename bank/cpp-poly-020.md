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

## Explanation

正确答案是 B, C, E。B 项 ``Foo` 不能被任何类继承，尝试继承会编译报错` 符合规则；C 项 ``Foo` 的对象仍然可以正常创建` 符合规则；E 项 `E` 符合规则；A 项 ``Foo` 可以被继承，`final` 只禁止重写 `bar`` 不满足该规则；D 项 ``Foo::bar()` 因为在 `final` 类中，所以不需要 `virtual`` 不满足该规则。多态题的关键是区分静态类型与动态类型：只有通过基类指针或引用调用虚函数时，才会发生运行期动态分派。常见误区是把普通成员函数、对象切片、构造/析构期调用也当成完整的虚调用场景。 多选题常见误区是只看关键字相似就勾选，而没有逐项检查它是否真的满足题干条件。
