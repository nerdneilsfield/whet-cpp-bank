---
qid: cpp-taste-param-003
type: single
kp: [cpp-functions, cpp-cpp14-17]
primary_kp: cpp-functions
difficulty: hard
answer_key: D
---

函数需要同时返回"商"和"余数"两个值。从**参数传递品味**的角度，哪段写得最好？

```cpp
// A
void divmod(int a, int b, int& q, int& r) {
    q = a / b;
    r = a % b;
}
```

```cpp
// B
void divmod(int a, int b, int* q, int* r) {
    *q = a / b;
    *r = a % b;
}
```

```cpp
// C
std::pair<int, int> divmod(int a, int b) {
    return {a / b, a % b};
}
```

```cpp
// D
struct DivResult { int quot; int rem; };
DivResult divmod(int a, int b) {
    return {a / b, a % b};
}
```

A. A 段：out 参数用引用最经典，避免空指针，且省掉返回值的拷贝。
B. B 段：指针 out 参数最灵活，调用方可以传 `nullptr` 表示"不需要那个值"。
C. C 段：返回 `std::pair`，调用方一行 `auto [q, r] = divmod(...)` 解构，简洁。
D. D 段：返回带具名字段的结构体，调用点 `r.quot` / `r.rem` 自解释，编译器照样 RVO。

## 解析

正确答案是 **D**。

- **A 段（差）**：调用点 `divmod(7, 3, x, y);` 完全看不出哪个是商哪个是余、也看不出参数会被修改；必须翻到函数签名才知道。两个 `int&` 还强迫调用方先声明两个变量、不能 `const`、不能直接 `auto`。
- **B 段（更差）**：指针多了空检查负担和 UB 风险（传 `nullptr` 即崩），灵活性是伪需求；C 风格 out 参数在 C++ 里只剩 C 互操作的理由。
- **C 段（差）**：`std::pair<int,int>::first/second` 在调用点是"魔法名"，读者根本不知道 `first` 是商还是余；交换两位也通不过编译器告警，靠注释维护。
- **D 段（好）**：具名字段让调用点完全自解释；结构体返回值同样享受 RVO/NRVO，性能与 out 参数等价甚至更好；C++17 起还能 `auto [q, r] = divmod(...)` 解构。这是"多 out 值"的现代答案。

**核心识别点：**
- 多个返回值优先用具名结构体，不要用引用/指针 out 参数。
- `std::pair`/`std::tuple` 只适合**临时**或**真正无意义命名**的组合（如 map 的 `(key, value)`）。
- RVO/NRVO 让"按值返回"在性能上等价于 out 参数；引用 out 参数已无性能借口。
- 引用 out 参数让调用点丢失"被修改"的信号，是可读性陷阱。

**来源：** C++ Core Guidelines F.21；Abseil tips of the week #88；Effective C++ Item 21。
