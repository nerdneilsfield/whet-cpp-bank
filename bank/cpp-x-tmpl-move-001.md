---
qid: cpp-x-tmpl-move-001
type: single
kp: [cpp-templates, cpp-move-semantics]
primary_kp: cpp-templates
difficulty: medium
answer_key: C
---

下列完美转发实现中，哪一种能正确地把实参的值类别（左值/右值）传递给 `g`？

```cpp
#include <utility>

void g(int&);
void g(int&&);

template <class T>
void fwd_A(T&& x) { g(x); }                       // A

template <class T>
void fwd_B(T&& x) { g(std::move(x)); }            // B

template <class T>
void fwd_C(T&& x) { g(std::forward<T>(x)); }      // C

template <class T>
void fwd_D(T x)   { g(std::forward<T>(x)); }      // D
```

A. fwd_A
B. fwd_B
C. fwd_C
D. fwd_D

---

**解析：**

`T&&` 在模板参数推导上下文中是 **转发引用（universal reference）**：传左值时 `T` 推为 `int&`，整体折叠为 `int&`；传右值时 `T` 推为 `int`，整体为 `int&&`。

- **A 错**：函数体内 `x` 是具名变量，始终是左值，永远调用 `g(int&)`，丢失右值性。
- **B 错**：无条件 `std::move(x)` 把左值实参也转成右值，破坏调用方意图。
- **C 对**：`std::forward<T>(x)` 根据 `T` 的推导结果有条件地恢复右值性——左值进左值出，右值进右值出，这正是完美转发的标准写法。
- **D 错**：参数按值传递，已发生一次拷贝/移动，`T` 也丢失了引用信息，`forward` 无意义。

完美转发的两个必要条件缺一不可：参数必须是 `T&&` 形式的转发引用 + 调用处必须用 `std::forward<T>`。
