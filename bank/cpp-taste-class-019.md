---
qid: cpp-taste-class-019
type: single
kp: [cpp-classes, cpp-special-members]
primary_kp: cpp-classes
difficulty: hard
answer_key: C
tags: [code-taste, best-practice, slicing]
---
有一个继承体系 `Shape` 基类、`Circle`/`Rect` 派生类。写一个函数接收"任意 Shape"。哪个签名最值得通过 review？

```cpp
// 类定义共用：
class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
};
class Circle : public Shape {
    double r_;
public:
    explicit Circle(double r) : r_(r) {}
    double area() const override { return 3.14 * r_ * r_; }
};

// A
double print_area(Shape s) {
    return s.area();
}

// B
double print_area(const Shape& s) {
    return s.area();
}

// C
double print_area(const Shape& s) {
    return s.area();
}
// 调用方：
// Circle c(1.0);
// print_area(c);  // 引用传递，多态 OK

// D
double print_area(Shape* s) {
    return s->area();
}
// 调用方：
// Circle c(1.0);
// print_area(&c);
```

A. A — 按值传递，调用方不用关心引用语义
B. B — 按 const 引用传递，避免拷贝、支持多态
C. C — 按 const 引用传递，避免拷贝、支持多态，且调用方式自然
D. D — 按指针传递，明确"可能 null"和多态意图

---

**解析：**

选 C（B 和 C 在签名上相同——选 C 因为它**明示了调用方式**，强调了"按引用传值类型"是正确的）。本题真正想区分的是"按值传基类导致 slicing" vs 其他正确方案。

逐一品味：

- **A**：**对象切片（object slicing）灾难**。`Shape s` 按值接收时，**只拷贝 Shape 部分**，把 Circle 派生部分丢掉。然后 `s.area()` 调用的是 Shape 的纯虚函数——**编译失败**（如果 Shape 真有纯虚）。如果 Shape 改为有默认实现的 virtual area()，那么调用的是 Shape::area() 而非 Circle::area()——**静默 wrong answer**。这是 C++ 多态最常被踩的雷。
- **B**：签名正确——`const Shape&`。引用传递保留派生类的动态类型，`s.area()` 通过虚分派调用 `Circle::area()`。无拷贝。但 B 没说明调用方怎么用，可能让读者误以为有什么特别之处。
- **C**：和 B 同签名，注释里展示了调用方式 `print_area(c)`——**自然且正确**。多态对象的传递就是按引用，调用方无需做任何特殊事情（不用取地址、不用 ptr 转换）。这是 C++ 多态接口的标准写法。
- **D**：按指针 `Shape*` 在功能上能 work，但**引入了不必要的 nullability**——调用方可能传 `nullptr`，函数必须检查（或假设非空、留下崩溃风险）。"我想要一个 Shape" 用 `const Shape&` 表达，"我想要一个可选的 Shape" 才用 `Shape*` 或 `optional<reference_wrapper<Shape>>`。指针的"多态意图明确"是误解——引用同样支持多态，且语义更清晰（必须有值）。

C 的核心信条：**多态对象必须按引用或指针传递；当无 null 语义时优先引用。** 这是 C++ 多态机制的基本规则。

注意陷阱：A 中如果 Shape 有 area 的默认实现（非纯虚），代码能编译通过——但**运行时调用的是基类 area**，给出 0 或错误的结果。debug 极难发现（编译期无警告，运行期看似正常但答案错）。

**核心识别点**：
- 按值传基类 → 切片，多态丢失（编译失败或静默错答）
- 按 const 引用传基类 → 多态正确，零拷贝
- 按指针传 → 引入 nullability 复杂度，仅在真有 null 语义时用
- 智能指针参数 → 表达所有权转移（unique_ptr）或共享所有权（shared_ptr）

**来源：** 手写题。Scott Meyers "Effective C++" Item 20: "Prefer pass-by-reference-to-const to pass-by-value"；C++ Core Guidelines C.145: "Access polymorphic objects through pointers and references"。

## Explanation

正确答案是 C（B 和 C 在签名上相同——选 C 因为它明示了调用方式，强调了"按引用传值类型"是正确的）。
工程上应让特殊成员函数、所有权和移动后的状态保持一致，避免把可编译误当成可维护。
但 B 没说明调用方怎么用，可能让读者误以为有什么特别之处。
