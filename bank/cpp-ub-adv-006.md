---
qid: cpp-ub-adv-006
type: single
kp: [cpp-undefined-behavior]
difficulty: medium
answer_key: B
---

下列代码读取 union 非活跃成员，行为是什么？

```cpp
union Data {
    int   i;
    float f;
};

int main() {
    Data d;
    d.f = 1.0f;         // f 是活跃成员
    int x = d.i;        // 读取非活跃成员 i
    return x;
}
```

A. 合法：union 的所有成员共享内存，读任意成员都是位重解释，行为明确
B. 在 C++ 中是 UB；C 语言中是实现定义行为（两者规则不同）
C. 合法当且仅当 `int` 和 `float` 大小相同
D. 只要程序员知道位布局就没有 UB

---

**解析：**

**C 语言（C99/C11）**：通过 union 读取非活跃成员是**实现定义行为**（implementation-defined），编译器必须记录结果，实践中大多数 C 编译器将其定义为位重解释。

**C++（C++11 及之后）**：标准只允许读取**最后一次写入的成员**（active member）。读取非活跃成员是 UB——编译器不需要记录任何行为。

主流 C++ 编译器（GCC、Clang）实践中通常产生"符合直觉"的位重解释结果，但这是扩展行为，不是标准保证。在优化代码中，编译器可能基于"仅 `f` 活跃"的假设删除无关代码，导致意外结果。

**正确做法（C++）：**
```cpp
float fval = 1.0f;
int ival;
std::memcpy(&ival, &fval, sizeof(ival));  // 合法的位重解释
```

## Explanation

正确答案是 B，即 在 C++ 中是 UB；C 语言中是实现定义行为（两者规则不同）。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
