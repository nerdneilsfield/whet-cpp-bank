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
