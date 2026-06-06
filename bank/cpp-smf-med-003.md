---
qid: cpp-smf-med-003
type: single
kp: [cpp-special-members]
difficulty: medium
answer_key: D
---

下列代码用 `-std=c++17` 编译，`Widget` 的拷贝/移动构造函数会被调用多少次？

```cpp
struct Widget {
    Widget()                 { std::puts("ctor"); }
    Widget(const Widget&)    { std::puts("copy"); }
    Widget(Widget&&)         { std::puts("move"); }
    ~Widget()                { std::puts("dtor"); }
};

Widget make() { return Widget{}; }     // 返回 prvalue

int main() {
    Widget w = make();                 // 关注这里
}
```

A. 调用 1 次 copy
B. 调用 1 次 move
C. 调用 1 次 copy 和 1 次 move
D. 既不调用 copy 也不调用 move，只输出 `ctor` 和 `dtor`

---

**解析：**

C++17 引入了**强制拷贝消除**（mandatory / guaranteed copy elision，[class.copy.elision]）。当 prvalue 用于初始化同类型对象时，标准要求**不存在**临时对象的物化，也不要求拷贝/移动构造函数可访问甚至存在——直接在目标位置构造。

`make()` 返回的是 prvalue `Widget{}`，`Widget w = make();` 在 C++17 中保证直接在 `w` 的存储位置调用默认构造，整个过程中既不发生拷贝也不发生移动。因此输出仅为 `ctor` 后接 `dtor`。

对比 C++14 及更早：NRVO 是“被允许但不强制”的优化，理论上可能调用 1 次 move（C++11 起 prvalue 优先匹配移动构造）。如果禁用了优化（如 `-fno-elide-constructors`，C++17 之前），就能看到 1 次 move 调用；但 C++17 之后**即使** `-fno-elide-constructors` 也不能撤销 prvalue 的强制消除（只能影响命名对象的 NRVO）。

## 解析

正确答案是 D，C++17 对返回 prvalue 并初始化同类型对象的场景有强制拷贝消除，直接在目标对象存储中构造。`Widget w = make();` 不需要也不会调用拷贝或移动构造，因此只看到构造和最终析构。不要用 C++14 及更早的可选优化规则来判断 C++17 题目。
