---
qid: cpp-taste-init-003
type: single
kp: [cpp-cpp11, cpp-type-sizes]
primary_kp: cpp-cpp11
difficulty: hard
answer_key: B
tags: [code-taste, best-practice, initialization, narrowing]
---
要从一个 `double r = ...` 算出一个 `int n`（用户希望"截断"），团队约定要写得**让 review 一眼能看出转换意图**。四个写法哪个最有品味？

```cpp
// A
int n = r;

// B
int n = static_cast<int>(r);

// C
int n(r);

// D
int n{r};
```

A. A — 隐式转换，最简洁
B. B — `static_cast` 写出来，意图明确
C. C — 函数风格转换，比 A 多一点显式
D. D — `{}` 是现代 C++ 推荐的统一初始化

---

**解析：**

选 B。这道题考 **"`{}` 防 narrowing 但不防错用，`static_cast` 才是表达截断意图的正确工具"**。

四个写法的真实行为：

- **A** `int n = r;` ：**隐式 narrowing**。`double → int` 是 narrowing conversion，编译器**通常只给 warning**（`-Wfloat-conversion` / `-Wconversion`），不阻止。在 review 里读到这一行，看不出作者是**有意截断**还是**忘了** `r` 是 `double`。意图缺失。
- **B** `int n = static_cast<int>(r);` ：**显式截断**。`static_cast` 这五个字符就是在向读者喊"我知道这里要损失精度，我同意"。这是 C++ Core Guidelines ES.46 / ES.49 的标准做法。能用，能审，能 grep 出来做安全审计。
- **C** `int n(r);` ：和 A 等价的 narrowing，**也只是 warning 级别**。"函数风格转换"是 C 风格强转的语法糖，**没比 A 多任何安全性**，反而因为长得像构造函数让读者更难判断意图。
- **D** `int n{r};` ：**编译失败**（或至少 ill-formed，标准要求拒绝）。`{}` 初始化禁止 narrowing conversion ——这是 `{}` 相对于 `()`/`=` 的**唯一硬安全特性**。所以 D 看上去"现代化"，**根本编不过**。如果作者真要走 `{}` 路线表达截断意图，正确写法是 `int n{static_cast<int>(r)};`——但那时 `{}` 就只是装饰了，意图全靠 `static_cast` 承担。

四个写法揭示的真相是：

| 写法 | narrowing | 意图 |
|------|-----------|------|
| `int n = r;` | 允许（warning） | 不清楚 |
| `int n(r);` | 允许（warning） | 不清楚 |
| `int n{r};` | **禁止（错误）** | 想表达"零损失"，但选错了 |
| `int n = static_cast<int>(r);` | 显式截断 | **明确** |

`{}` 的"防 narrowing"是一个**编译期断言**——"我保证这里没有精度损失"。如果你**有意要截断**，`{}` 反而是错的工具。这条规则反直觉，很多人记成"`{}` 总是更安全"——实际上 `{}` 是更严格，严格到不允许你做你想做的事时就是错配。

**核心识别点**：

- `double → int`、`long → int`、`int → short`、`int → char` 这些 narrowing，**`{}` 一律拒绝**
- 想表达"我接受精度损失"——用 `static_cast<T>(...)`
- 想表达"我保证类型完全匹配"——用 `{}`
- C 风格强转 `(int)r` 和函数风格 `int(r)` 在 review 里都该被改成 `static_cast`，因为它们隐藏了 reinterpret/const 转换的可能性
- 隐式转换的"简洁"是技术债——半年后看到那一行的人不知道是 bug 还是有意

`{}` 在 C++11 设计时被宣传为 "uniform initialization"，但它的"统一"是有代价的——**vector 的劫持**（题1）、**narrowing 禁止**（本题）、**explicit 构造函数行为差异**——使它没成为真正的统一。Bjarne 本人后来承认这是 C++11 的设计妥协之一。

**来源：** 手写题。narrowing 规则见 ISO/IEC 14882 §8.5.4 [dcl.init.list]/7；C++ Core Guidelines ES.46 "Avoid lossy (narrowing, truncating) arithmetic conversions"、ES.49 "If you must use a cast, use a named cast"。

## Explanation

正确答案是 B。如果作者真要走 `{}` 路线表达截断意图，正确写法是 `int n{static_cast<int>(r)};`——但那时 `{}` 就只是装饰了，意图全靠 `static_cast` 承担。
"函数风格转换"是 C 风格强转的语法糖，没比 A 多任何安全性，反而因为长得像构造函数让读者更难判断意图。
这道题考 "`{}` 防 narrowing 但不防错用，`static_cast` 才是表达截断意图的正确工具"。
