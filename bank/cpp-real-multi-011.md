---
qid: cpp-real-multi-011
type: multi
kp: [cpp-special-members, cpp-move-semantics]
primary_kp: cpp-special-members
difficulty: medium
answer_key: [A, B, D]
tags: [interview-real, multi-vendor]
---
```cpp
class Widget {
public:
    Widget() = default;
    Widget(const Widget&) { std::cout << "copy ctor\n"; }
    Widget(Widget&&) noexcept { std::cout << "move ctor\n"; }
};

Widget makeWidget() {
    Widget w;
    return w;       // 调用 (?)
}

void func(Widget w) { /* ... */ }

int main() {
    Widget a;
    Widget b = a;             // (1)
    Widget c = std::move(a);  // (2)
    func(b);                  // (3)
    func(std::move(b));       // (4)
    Widget d = makeWidget();  // (5)
}
```
以下哪些语句会**调用拷贝构造函数**（输出 "copy ctor"）（多选）？

A. (1) `Widget b = a;`
B. (3) `func(b);` —— 按值传 lvalue
C. (4) `func(std::move(b));`
D. 当 Widget 没有定义移动构造时，(2) `Widget c = std::move(a);`
E. (5) `Widget d = makeWidget();` —— 在 C++17 mandatory copy elision 下

---

**解析：**

正确答案：**A、B、D**。

**逐项分析：**

**A 正确：** `Widget b = a;` 中 a 是 lvalue → 调用拷贝构造（"copy ctor"）。

**B 正确：** `func(b)` 中 b 是 lvalue → 按值传递时调用拷贝构造（"copy ctor"）。

**C 错误：** `func(std::move(b))` 中 std::move 转 b 为 rvalue → 调用移动构造（"move ctor"）。

**D 正确：** 如果 Widget 没有定义移动构造（也没有删除），且有拷贝构造：
- `std::move(a)` 把 a 转为 xvalue
- 重载决议查找匹配 → 找不到移动构造 → 回退到 `Widget(const Widget&)`（const 引用可绑定 rvalue）
- → 调用拷贝构造

题目中 Widget **定义了** 移动构造（"move ctor"），所以实际 (2) 输出 "move ctor"。但题干 D 提的是"假如没有移动构造"的情况，此时确实退化为拷贝。

**E 错误：** C++17 mandatory copy elision：
- `makeWidget()` 返回一个 prvalue（实际上返回值 NRVO 也常被优化）
- `Widget d = makeWidget();` 直接物化 prvalue 到 d
- **不调用任何拷贝/移动构造**
- 注意：`makeWidget()` 内部 `return w;` 是返回**具名局部变量** w → NRVO（C++17 仍是可选优化，但通常发生）→ 即便不发生 NRVO，也调用 move（不是 copy）

**完整输出（假设 C++17 + NRVO 发生）：**
```
copy ctor     // (1)
move ctor     // (2)
copy ctor     // (3)
move ctor     // (4)
              // (5) - 全部省略
```

**记忆要点：**
- 按值传 lvalue → copy
- 按值传 rvalue → move
- NRVO/copy-elision → 既不 copy 也不 move
- 没有 move 时 → fall back to copy

**来源：** 跨厂 C++ 移动语义经典题（参考：Effective Modern C++ Item 25）