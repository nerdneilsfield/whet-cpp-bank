---
qid: cpp-real-tencent-006
type: single
kp: [cpp-cpp14-17, cpp-functions]
primary_kp: cpp-cpp14-17
difficulty: hard
answer_key: C
tags: [interview-real, tencent]
---
```cpp
struct Widget { Widget() { std::cout << "C"; } 
                Widget(const Widget&) { std::cout << "c"; }
                Widget(Widget&&) noexcept { std::cout << "m"; }
                ~Widget() { std::cout << "D"; } };

Widget makeWidget() {
    return Widget();   // 返回临时对象
}

int main() {
    Widget w = makeWidget();
    return 0;
}
```
分别用 C++11、C++14、C++17 编译并禁用所有优化（如 `-fno-elide-constructors`）时输出对比，再启用默认优化时输出。以下说法正确的是：

A. 在 C++17 中即使禁用优化，也只输出 "CD"，因为 RVO 是强制的
B. 在所有 C++ 版本中，禁用优化都会输出 "CmmD"
C. C++17 起的**保证 copy elision**（强制省略），makeWidget() 返回 prvalue 时不会调用拷贝/移动构造（即使禁用 -fno-elide-constructors），输出 "CD"；C++11/14 可能输出 "CmmD" 或经优化省略
D. C++17 删除了拷贝/移动构造的概念

---

**解析：**

选 C。这道题考察 C++17 引入的 **mandatory copy elision（强制省略）**。

**C++11/14 行为：**
- `return Widget()` 创建一个临时对象（prvalue）
- 隐式从该临时对象**移动构造**到返回值临时
- 再**移动构造**到 w
- 优化（NRVO/RVO）可省略移动构造，但**编译器不强制必须省略**

**C++17 引入了一个根本变化：**
- prvalue 不再是"对象"，而是"对象的构造表达式"
- `Widget()` 是 prvalue，可以**直接物化（materialize）** 到目标位置
- `return Widget();` 中，Widget() 直接构造在调用方的栈帧
- `Widget w = makeWidget();` 中，prvalue 直接物化为 w
- **不需要拷贝/移动构造**，甚至**Widget 即使没有拷贝/移动构造函数也能编译通过**

**结果对比（启用 `-fno-elide-constructors`）：**
- C++11/14: `CmmD`（构造 + 两次移动 + 析构）
- C++17: `CD`（构造 + 析构）

注意区分：
- **强制省略（C++17）**：prvalue 直接物化，必须省略
- **NRVO**（具名返回值优化）：返回局部变量名，**C++17 也只是可选优化**

A 错：表述近似正确但"RVO 是强制的"不准确。准确说法是 prvalue 物化机制是强制的，NRVO 不是。

**来源：** 腾讯 / 字节 C++ 高级面试（参考：cppreference Copy elision、C++17 标准 P0135R1）

## Explanation

正确答案是 C。
选 C。这道题考察 C++17 引入的 mandatory copy elision（强制省略）。
A 错：表述近似正确但"RVO 是强制的"不准确。准确说法是 prvalue 物化机制是强制的，NRVO 不是。
