---
qid: cpp-class-hard-003
type: single
kp: [cpp-classes]
difficulty: hard
answer_key: C
---

CRTP 中使用模板成员函数时，以下哪个调用是正确的？

```cpp
template<typename Derived>
struct Base {
    template<typename T>
    void f(T t) { static_cast<Derived*>(this)->g(t); }
};

struct D : Base<D> {
    void g(int) {}
};

int main() {
    D d;
    d.f(42);    // ①
    d.f(3.14);  // ②
}
```

两个调用是否编译成功？

A. ① 和 ② 均正常
B. ① 正常，② 编译错误因为 `double` 到 `int` 的隐式转换被禁止
C. ① 正常，② 在 `Base::f` 实例化时，`D::g(int)` 已声明但类型不匹配 `double`，通过隐式转换仍然成功
D. ① 失败，因为 CRTP 中模板成员函数不能调用派生类方法

## Explanation

CRTP 中通过 `static_cast<Derived*>(this)->g(t)` 调用派生类方法是经典用法。核心关注点是**两阶段查找（two-phase lookup）**：`Base<D>::f<double>` 在 `main` 调用 `d.f(3.14)` 时实例化（第二阶段），此时 `D` 已经完整定义，`D::g(int)` 可见。`t` 为 `double`，通过隐式标准转换（浮点→整数）匹配 `g(int)`，调用成功。C++ 允许这种隐式转换，尽管会截断。因此 ① 和 ② 均编译。本题陷阱在于部分程序员认为 `double` 不能隐式转 `int`（其实可以，只不过有精度丢失警告）。
