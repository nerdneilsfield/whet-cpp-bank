---
qid: cpp-poly-adv-012
type: single
kp: [cpp-polymorphism]
difficulty: medium
answer_key: B
---

以下手写类型擦除代码，`invoker(obj, 10)` 会调用哪个函数？

```cpp
#include <cstdio>

struct Erased {
    void* data;
    void (*invoke)(void*, int);
};

struct Printer {
    int id;
    void print(int x) { printf("Printer%d: %d\n", id, x); }
};

void printer_invoke(void* obj, int x) {
    static_cast<Printer*>(obj)->print(x);
}

int main() {
    Printer p{42};
    Erased obj{ &p, printer_invoke };
    obj.invoke(obj.data, 10);   // 调用哪个函数？
}
```

A. 未定义行为：`void*` 转 `Printer*` 的 `static_cast` 不合法
B. `Printer::print`，输出 `Printer42: 10`
C. `printer_invoke` 直接打印，但 `id` 值不可预期（`void*` 信息丢失）
D. 编译错误：函数指针类型 `void(*)(void*, int)` 不能存储成员函数

---

**解析：**

这是**手写类型擦除**的最小模式：`void* data` 存储对象地址，`void(*invoke)(void*, int)` 是一个自由函数指针，负责恢复类型并调用方法。

- `printer_invoke` 接受 `void* obj`，通过 `static_cast<Printer*>(obj)` 恢复类型（合法：原始对象确实是 `Printer`），然后调用 `print(x)`。
- `p.id = 42`，`x = 10`，输出 `Printer42: 10`。
- `static_cast<Printer*>(void*)` 在原始对象确实是 `Printer` 时完全合法（不同于 `reinterpret_cast`，虽然结果相同，但语义更清晰）。

此模式是 `std::function`、`std::any` 等类型擦除设施的底层原理缩影。

## Explanation

正确答案是 B，因为该选项对应 ``Printer::print`，输出 `Printer42: 10``，符合题中代码或概念的 C++ 语义。多态题的关键是区分静态类型与动态类型：只有通过基类指针或引用调用虚函数时，才会发生运行期动态分派。常见误区是把普通成员函数、对象切片、构造/析构期调用也当成完整的虚调用场景。 A 项、C 项、D 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
