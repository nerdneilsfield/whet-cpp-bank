---
qid: cpp-taste-param-013
type: single
kp: [cpp-polymorphism, cpp-functions]
primary_kp: cpp-polymorphism
difficulty: hard
answer_key: D
---

`render` 需要接受**多态**的 `Shape`（支持派生 `Circle`/`Square`），调用 `draw()` 但**不接管所有权**。从**参数传递品味**的角度，哪段最合适？

```cpp
// A
void render(std::unique_ptr<Shape> s) {
    s->draw();   // 用完销毁
}
```

```cpp
// B
void render(Shape* s) {
    if (s) s->draw();
}
```

```cpp
// C
void render(std::shared_ptr<Shape> s) {
    s->draw();
}
```

```cpp
// D
void render(const Shape& s) {
    s.draw();
}
```

A. A 段：unique_ptr 明确表达"我销毁这个形状"，语义最精确。
B. B 段：裸指针最轻量，nullptr 检查保证空安全性。
C. C 段：shared_ptr 引用计数共享，调用方可以继续持有引用。
D. D 段：const 引用表达"只看不存"，虚函数通过引用正常工作。

## 解析

正确答案是 **D**。

- **A 段（错）**：函数只是"调一下 draw"却传递了"我要销毁 Shape"的所有权意图——调用方不敢再存自己的指针。如果调用方栈上构造了 `Circle c; render(std::move(c));` 的类型都不能匹配。把不相关的所有权语义强行注入参数类型。
- **B 段（差）**：裸指针是最危险的"可选"形式：是否要检查 nullptr？调用方是否为函数分配了对象？API 没有类型承诺。`Shape*` 既可以表示"单个形状"也可以表示"数组的开头"，读者要猜。现代 C++ 里的裸指针已经缩小到"可选引用"的 role，但仍然没有类型约束。
- **C 段（差）**：`shared_ptr<Shape>` 暗示"这个函数也会共享所有权并延长生命周期"——但 render 只调用 draw，画完就走。引入原子引用计数开销、强迫调用方用 shared_ptr，是 `shared_ptr` 污染的典型例子。和 A 类似的"语义不匹配"。
- **D 段（好）**：`const Shape&` 传递的是"我可以画这个形状，画完不管它的生命周期"。虚函数对引用正常工作（`s.draw()` 是虚分派）。调用方持有的是 `Circle` 栈对象、`unique_ptr<Circle>` 的 `*p`、`shared_ptr<Circle>` 的 `*p`，全部能传入。"只看不存"→传引用。这是 C++ 多态观察者的标准范式。

**核心识别点：**
- 只做多态**观察**不接管生命周期：传 `const Base&` / `Base&`，不要传智能指针。
- 裸指针 `Base*` 只用在"可能为空且不能改签名"的遗留代码或可选引用场景。
- `unique_ptr<Base>` 参数表达"我要消除它"，不该出现在只读函数签名里。
- `shared_ptr<Base>` 参数表达"我持有引用计数的一份"，对只读场景全是浪费。
- 引用上的虚调用和指针上的虚调用一样合法、一样有效率。

**来源：** C++ Core Guidelines R.30 （"不存就传 T*，存就传 unique_ptr/shared_ptr"）；Herb Sutter "GotW #89"；Bjarne Stroustrup "C++ programming language 4th ed." 31.3。