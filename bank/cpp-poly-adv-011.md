---
qid: cpp-poly-adv-011
type: multi
kp: [cpp-polymorphism]
difficulty: medium
answer_key: [B, C]
---

关于 `std::function` 相比裸函数指针的**额外开销**，哪些说法正确？（多选）

```cpp
#include <functional>

void plain(int x) {}

int main() {
    void (*fp)(int) = plain;          // 裸函数指针
    std::function<void(int)> fn = plain; // std::function
    fn(42);
}
```

A. `std::function` 与裸函数指针调用开销完全相同，只是语法糖
B. `std::function` 内部通过类虚表（或等价的函数指针间接调用）分派，每次调用有间接开销
C. `std::function` 存储 lambda（含捕获）时，若捕获数据超出内联缓冲区大小，会发生堆分配
D. `std::function` 可以存储任意可调用对象，但编译器会为每种类型内联展开，无运行时开销

---

**解析：**

- **A 错误**：`std::function` 使用类型擦除，调用路径包含至少一次间接跳转（通过内部函数指针或虚调用），比裸函数指针多一层间接。
- **B 正确**：`std::function` 的 `operator()` 内部通过一个函数指针（或等价机制）调用存储的可调用对象，这是类型擦除的代价。
- **C 正确**：`std::function` 同样有 SBO（通常约 16~24 字节）。若存储的 lambda 捕获了大量数据（超出内联缓冲区），会在堆上分配存储空间，引入 `malloc`/`free` 开销。
- **D 错误**：`std::function` 是运行时多态工具，不做编译期内联展开；若需要零开销，应用模板参数或 `auto` 存储可调用对象。
