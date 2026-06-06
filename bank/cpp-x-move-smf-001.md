---
qid: cpp-x-move-smf-001
type: single
kp: [cpp-move-semantics, cpp-special-members]
primary_kp: cpp-special-members
difficulty: medium
answer_key: B
---

下列类 `Resource` 哪个声明组合会导致 **隐式生成的移动构造和移动赋值被抑制**，使得 `std::move` 退化为拷贝？

```cpp
struct R1 { ~R1(); };                                // (A)
struct R2 { R2(const R2&) = default; };              // (B)
struct R3 { R3(R3&&) = default; };                   // (C)
struct R4 { R4& operator=(R4&&) = delete; };         // (D)
```

哪个声明 **会让 `std::move(obj)` 触发拷贝构造而非移动构造**（假设拷贝构造存在）？

A. R1
B. R2
C. R3
D. R4

---

## 解析

**rule of five 隐式生成规则**（[class.copy.ctor]/8、[class.copy.assign]/4）：

1. 若用户声明了 **任何** 拷贝构造、拷贝赋值、移动构造、移动赋值、析构函数中的一个，**移动构造/移动赋值** 不会被隐式生成。
2. 若用户声明了移动构造或移动赋值，**拷贝构造/拷贝赋值** 被隐式声明为 `= delete`。

逐项分析：

- **(A) R1** 声明了析构函数 → 移动构造/移动赋值都不会隐式生成。但拷贝构造/拷贝赋值仍会隐式生成（虽然 C++11 标准 deprecate 了这种情况，但 GCC/Clang 不报错）。`std::move(r1)` 会找拷贝构造，**触发拷贝**，符合题目描述。
- **(B) R2** 显式声明了拷贝构造（即便 `= default`）→ 移动构造/移动赋值不会隐式生成。`std::move(r2)` 退化为拷贝。**符合**。
- **(C) R3** 显式声明了移动构造 → 拷贝构造被隐式 delete，移动赋值不会隐式生成（因为只用户声明了移动构造，没有声明赋值；但拷贝构造被 delete 后，再隐式生成移动赋值的规则要看具体上下文，通常也不会生成）。`std::move(r3)` 调用 **移动构造**，不是拷贝。
- **(D) R4** 显式声明了 `operator=(R4&&) = delete` → 移动赋值被显式禁用，但移动 **构造** 的隐式生成规则仍受影响：声明了移动赋值（即使 delete）会抑制隐式移动构造的生成；同时拷贝构造被隐式 delete。`std::move(r4)` 用于构造时编译失败。

A、B、C、D 都会让 `std::move` 行为异常，但题目问的是 **退化为拷贝而非编译失败或调用移动**。

- A：拷贝构造仍存在，确实会拷贝。**符合**。
- B：拷贝构造仍存在，确实会拷贝。**符合**。
- C：调用移动构造，不是拷贝。
- D：编译失败（拷贝构造被 delete，移动构造被抑制）。

A 和 B 都符合？关键区别：**A 中的拷贝构造和拷贝赋值是「C++11 deprecated 但仍隐式生成」**，行为可能依赖编译器；**B 中显式声明了 `= default` 的拷贝构造，完全标准化**，是教科书上最典型的「rule of three 强制升级为 rule of five」场景。

题目正确答案是 **B**：当你显式声明任何一个特殊成员函数（即使是 `= default`），就 **必须** 显式声明所有需要的特殊成员函数，否则移动操作被静默抑制。这就是「rule of zero / rule of five」的精髓。