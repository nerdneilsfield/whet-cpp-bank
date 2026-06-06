---
qid: cpp-taste-param-014
type: single
kp: [cpp-functions, cpp-memory-mgmt, cpp-polymorphism]
primary_kp: cpp-functions
difficulty: hard
answer_key: A
---

根据形状类型字符串（`"circle"`/`"square"`）构造相应的派生类对象。从**参数传递品味**的角度，哪段最合适？

```cpp
// A
std::unique_ptr<Shape> make_shape(std::string_view type) {
    if (type == "circle") return std::make_unique<Circle>(/*...*/);
    if (type == "square") return std::make_unique<Square>(/*...*/);
    return nullptr;
}
```

```cpp
// B
std::shared_ptr<Shape> make_shape(std::string_view type) {
    if (type == "circle") return std::make_shared<Circle>(/*...*/);
    if (type == "square") return std::make_shared<Square>(/*...*/);
    return nullptr;
}
```

```cpp
// C
Shape make_shape(std::string_view type) {
    if (type == "circle") return Circle(/*...*/);
    if (type == "square") return Square(/*...*/);
    throw std::invalid_argument("unknown type");
}
```

```cpp
// D
Sphere make_shape(std::string_view type, Shape*& out) {
    if (type == "circle") { out = new Circle(/*...*/); return 0; }
    if (type == "square") { out = new Square(/*...*/); return 0; }
    out = nullptr;
    return -1;
}
```

A. A 段：返回 `unique_ptr<Shape>`，类型正确表达"工厂生成了一个独占所有权多态对象"。
B. B 段：返回 `shared_ptr<Shape>`，调用方立即能有共享语义，最灵活。
C. C 段：按值返回 Shape 是走切片（slicing），但用异常处理未知类型。
D. D 段：out 指针 + int 返回码，调用方能自己管理状态。

## 解析

正确答案是 **A**。

- **A 段（好）**：工厂函数返回 `unique_ptr` 是 C++ 多态工厂的标准范式。`Circle`/`Square` 是堆分配的（只有堆上的多态对象才有安全、明确的生命周期），所有权通过 `unique_ptr` 明确给了调用方。调用方可以存、move、或释放；如果需要共享，显式 `std::shared_ptr<Shape>(std::move(p))` 转换——多走一步但不损失信息。
- **B 段（差）**：`make_shared` 可能更高效（控制块和对象在一块内存），但函数**预判**了调用方需要 `shared_ptr`——如果调用方只需要独占或不需要多态（纯用 `auto` 接收），就不该付出原子引用计数开销。函数应返回最少承诺，由调用方选择包装。
- **C 段（错）**：按值返回 `Shape` 会**切片**（object slicing）：尽管 `Circle(/*...*/)` 的构造函数没问题，但返回时对象被截断成 `Shape` 部分，虚表被替换为 `Shape` 的——`Shape sh = make_shape("circle"); sh.draw();` 调的是 `Shape::draw`，不是 ` Circle::draw`。这是一个沉默的语义错误，编译器不报错。
- **D 段（更差）**：`new` 裸指针 + 返回值码的组合是 C++ 要根治的模式——异常不安全（如果后续操作异常就泄漏了）、调用方靠人力记 `delete`、没有类型承诺告诉调用方"delete 进制是 default_delete 还是其他"。out 参数需要先声明指针再接收，比返回值复杂得多。

**核心识别点：**
- 多态工厂函数的标准返回类型：`std::unique_ptr<Base>`。
- `shared_ptr` 返回是"过度承诺"——调用方可以取 `unique_ptr` 升级，但反过来不行。
- 按值返回基类 = 切片，多态丢失，是沉默的 bug。
- 裸 `new` + out 参数是 80 年代的写法，在 C++11 后的代码中已经退役。
- 工厂的堆分配不是缺点：多态对象必须通过指针/引用访问，堆是唯一方案。

**来源：** C++ Core Guidelines C.50/C.149/F.18；Effective Modern C++ Item 18/21；CppCon "The 'Factory'" 多场。