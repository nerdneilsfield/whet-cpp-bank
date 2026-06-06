---
qid: cpp-enum-med-001
type: single
kp: [cpp-enum]
difficulty: medium
answer_key: A
---

C++11 `enum class` 与旧式 `enum` 的关键区别之一是隐式转换行为。以下哪段代码会编译失败？

A.
```cpp
enum class Color { Red, Green, Blue };
int x = Color::Red;
```

B.
```cpp
enum class Color { Red, Green, Blue };
Color c = Color::Red;
bool eq = (c == Color::Red);
```

C.
```cpp
enum Color { Red, Green, Blue };
int x = Red;
```

D.
```cpp
enum class Color { Red, Green, Blue };
int x = static_cast<int>(Color::Red);
```

---

**解析：**

`enum class`（有作用域枚举）**不提供**到整型的隐式转换。`Color::Red` 是 `Color` 类型，不能隐式赋值给 `int`。这是与旧式 `enum`（无作用域枚举）的核心区别之一——旧式枚举可以隐式转换为 `int` 等整型。

手动 `static_cast<int>(Color::Red)` 或定义 `operator int()` 才能通过编译。其余选项：B 中 `enum class` 的比较合法；C 是旧式 `enum` 合法；D 用 `static_cast` 合法。

## 解析

正确答案是 A。`enum class` 是有作用域、强类型枚举，枚举器需用枚举名限定且不会隐式转为整数。选项 A 的表述“｀｀｀cpp enum class Color { Red, Green, Blue }; int x = Color::Red; ｀｀｀”正好符合该规则。B、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
