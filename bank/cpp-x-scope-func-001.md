---
qid: cpp-x-scope-func-001
type: single
kp: [cpp-scope-linkage, cpp-functions]
primary_kp: cpp-scope-linkage
difficulty: medium
answer_key: C
---

以下两个文件编译并链接，最终 `f` 被调用了哪个定义？

```cpp
// --- a.cpp ---
inline int f() { return 1; }
int call_from_a() { return f(); }

// --- b.cpp ---
inline int f() { return 2; }
int call_from_b() { return f(); }

// 假设用 -O0 编译，无 LTO
```

A. 链接失败：多重定义（ODR 违反，链接报错）
B. 两者都链接成功，`call_from_a()` 返回 2，`call_from_b()` 返回 2（后定义的获胜）
C. 两者都链接成功，但结果未定义——inline 函数的 ODR 违反「相同定义」要求
D. 链接成功，`call_from_a()` 返回 1，`call_from_b()` 返回 2（各自调用自己的版本）

---

**解析：**

**ODR 对 inline 函数的特殊规则**（[basic.def.odr]/6）：

`inline` 函数（或函数模板、类内的 `constexpr` 函数）允许在多个翻译单元定义，且链接器会 **合并** 它们（通过 COMDAT 段机制）。但这是 **有条件的**：所有翻译单元中的定义必须 **完全一致（token-by-token）**。

这里 `a.cpp` 中 `f()` 返回 1，`b.cpp` 中 `f()` 返回 2，显然不是相同定义。

[basic.def.odr]/15：如果多个翻译单元中 `inline` / `constexpr` 函数定义不相同，行为是 **未定义行为（不需要诊断）**。

- **A 错**：链接器不会报错。多个 COMDAT 段之间的不同定义不会触发多重定义错误，因为 inline 函数上的 COMDAT 允许重复，链接器可能选择任意一个副本（通常取第一个出现的，或生成 stub）。**没有诊断义务**。
- **B 错**：这只是可能的结果之一，不是保证的。不同编译器、不同优化级别表现不同。
- **C 对**：UB，任何结果都可能，包括：
  - 两处都返回同一个值（如两者都调用 `a.cpp` 的版本）
  - 两处各自调用自己的版本（依赖于是否内联展开）
  - 优化器把其中一个内联展开金融级错误
- **D 错**：否，如果链接器只保留了一个副本（常见行为），两处都可能调用同一个。

可靠方式：在不同的翻译单元使用 **相同的 inline 定义**，通常通过头文件包含实现：

```cpp
// f.h
inline int f() { return 42; }  // 一个定义，包含到所有 TU
```

而非在两个 .cpp 里手写不同定义。