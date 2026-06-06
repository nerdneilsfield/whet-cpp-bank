---
qid: cpp-poly-adv-004
type: multi
kp: [cpp-polymorphism]
difficulty: medium
answer_key: [A, C]
---

关于 CRTP 的**限制**，下列说法哪些正确？（多选）

```cpp
template <typename D>
struct Shape { void draw() { static_cast<D*>(this)->draw_impl(); } };

struct Circle : Shape<Circle> { void draw_impl(); };
struct Square : Shape<Square> { void draw_impl(); };

// 试图统一存储：
// std::vector<Shape*> shapes;  // ← 能通过编译吗？
```

A. `Shape<Circle>` 和 `Shape<Square>` 是两个**不同**的类型，不存在公共基类，无法放入同一个 `Shape*` 容器
B. 可以用 `Shape<void>*` 作为公共基类指针统一存储所有 CRTP 实例
C. CRTP 是静态多态，若需要运行时异构容器，必须引入额外的虚函数层或类型擦除
D. CRTP 派生类可以隐式转换为 `Shape<Circle>*` 和 `Shape<Square>*`，两者可以存入同一 `std::vector`

---

**解析：**

- **A 正确**：`Shape<Circle>` 与 `Shape<Square>` 是模板实例化出的两个独立类型，彼此没有继承关系，不能用同一指针类型统一管理。`std::vector<Shape*>` 中 `Shape` 是一个需要具体模板参数的模板，裸写 `Shape*` 无法编译（除非有非模板公共基类）。
- **B 错误**：`Shape<void>` 只是另一个模板实例，不是 `Shape<Circle>` 的基类。
- **C 正确**：若需运行时多态，需要在 CRTP 层之上叠加虚函数（二层设计）或使用 `std::any`/`std::variant`/手写类型擦除。
- **D 错误**：两种指针类型不同，`std::vector` 只能存一种元素类型。
