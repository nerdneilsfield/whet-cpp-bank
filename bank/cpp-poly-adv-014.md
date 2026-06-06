---
qid: cpp-poly-adv-014
type: single
kp: [cpp-polymorphism]
difficulty: hard
answer_key: B
---

以下代码能否编译？若不能，原因是什么？若能，如何绕过限制？

```cpp
struct Base {
    template <typename T>
    virtual void process(T value);   // ← 虚函数模板？
};

struct Derived : Base {
    template <typename T>
    void process(T value) override { /* ... */ }
};
```

A. 可以编译：C++ 允许虚函数模板，编译器会为每种 `T` 生成独立的 vtable 条目
B. 编译错误：虚函数不能是函数模板，因为 vtable 大小必须在编译期固定，而模板的实例化集合无界
C. 可以编译，但 `override` 关键字会被忽略，实际上不是虚函数
D. 可以编译，但只有 `T = int` 和 `T = double` 等内置类型有效

---

**解析：**

**编译错误**（选项 B）。C++ 标准明确禁止虚函数模板（§11.7.2 [temp.mem]/7）。

**根本原因**：vtable 是编译期静态数组，其大小（虚函数个数）必须在类定义完成时确定。若允许虚函数模板，`process<int>`、`process<double>`、`process<MyClass>`… 的实例化是无限的，vtable 无法预先分配固定槽位。

**绕过方法**（常见三种）：

1. **类型擦除参数**：改为 `virtual void process(std::any value)`，在内部 `any_cast`。
2. **访问者模式**：`virtual void accept(Visitor&)` + 模板 `Visitor`。
3. **双层设计**：外层虚函数接受类型标记（`std::type_index`）或 `void*`，内层模板负责类型恢复。

```cpp
// 绕过示例：类型擦除
struct Base {
    virtual void process(std::any value) = 0;  // 合法：非模板虚函数
};
```

## 解析

正确答案是 B，因为该选项对应 `编译错误：虚函数不能是函数模板，因为 vtable 大小必须在编译期固定，而模板的实例化集合无界`，符合题中代码或概念的 C++ 语义。多态题的关键是区分静态类型与动态类型：只有通过基类指针或引用调用虚函数时，才会发生运行期动态分派。常见误区是把普通成员函数、对象切片、构造/析构期调用也当成完整的虚调用场景。 A 项、C 项、D 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
