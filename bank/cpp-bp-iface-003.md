---
qid: cpp-bp-iface-003
type: single
kp: [cpp-polymorphism]
difficulty: medium
answer_key: A
---

下面的多态使用代码会导致内存泄漏，原因？

```cpp
class Shape {
public:
    virtual double area() const = 0;
    ~Shape() {}                      // (1)
};

class Circle : public Shape {
    double r_;
    double* big_buffer_ = new double[1000];   // 模拟资源
public:
    Circle(double r) : r_(r) {}
    ~Circle() { delete[] big_buffer_; }       // (2)
    double area() const override { return 3.14 * r_ * r_; }
};

int main() {
    Shape* s = new Circle(1.0);
    delete s;                        // ← 这里
}
```

A. Shape 的析构函数不是虚函数，delete 基类指针只调 ~Shape()，不调 ~Circle()，big_buffer_ 泄漏
B. Circle 的析构函数应该是虚函数
C. delete[] 用错了，应该用 delete
D. Circle 应该用 unique_ptr<double[]> 才正确

---

## 解析

C++ 规则：通过基类指针 `delete` 派生类对象，**只有当基类析构函数是 virtual 时**，才会调用派生类析构函数。否则**仅调用基类析构**，派生类资源泄漏（且是 UB）。

本例 `~Shape()` 不是 virtual：
- `delete s;` 只调用 `~Shape()`
- `Circle::big_buffer_` 永远不被释放
- 这是**未定义行为**（标准明确规定通过非虚析构的基类指针 delete 派生类对象是 UB）

正确的多态基类设计准则：

**如果有任何 virtual 函数，析构必须 virtual。**

```cpp
class Shape {
public:
    virtual double area() const = 0;
    virtual ~Shape() = default;        // ← 必须 virtual
};
```

变体：
1. **多态基类**：`virtual ~T() = default;` 是标准
2. **不该被继承的类**：标 `final`：`class Widget final { ... };`
3. **保护性析构（NVI变种）**：`protected ~Base() {}` + 派生类必须自己提供 public 析构。这避免了 "通过基类指针 delete" 的可能性，但要求所有使用都用具体类型

补充：现代 C++ 推荐避免裸指针多态，用智能指针：
```cpp
std::unique_ptr<Shape> s = std::make_unique<Circle>(1.0);
// 自动析构，但 ~Shape() 仍必须 virtual！
```

智能指针不能"自动修复"基类非虚析构的问题，本质上 unique_ptr 内部还是调 `delete`。

工具：
- `-Wnon-virtual-dtor`（Clang/GCC）：基类有虚函数但析构非虚时警告