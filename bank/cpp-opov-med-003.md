---
qid: cpp-opov-med-003
type: single
kp: [cpp-operator-overload]
difficulty: medium
answer_key: D
---

给定以下两个类，分别声明转换运算符为隐式与 `explicit`，哪些表达式能通过编译？

```cpp
struct A { operator bool() const { return true; } };           // 隐式
struct B { explicit operator bool() const { return true; } };  // 显式 (C++11)

A a;  B b;
int  s1 = a + 1;            // ①
int  s2 = b + 1;            // ②
if (a) {}                   // ③
if (b) {}                   // ④
bool x = a;                 // ⑤
bool y = b;                 // ⑥
```

A. ①②③④⑤⑥ 全部合法
B. 只有 ①③⑤ 合法，②④⑥ 全部报错
C. ①②③④⑤⑥ 中 ② 和 ⑥ 报错，其他合法
D. ①③④⑤ 合法；② 和 ⑥ 报错

---

**解析：**

`explicit operator bool` 与普通 `operator bool` 的关键差别在于**上下文转换**（contextual conversion to bool）：`if`、`while`、`for`、`!`、`&&`、`||`、`?:` 的条件位置允许使用 `explicit` 转换；其他位置（拷贝初始化、算术表达式、函数实参）则不允许。

逐项判定：
- ① `a + 1`：隐式 `bool` 可参与整型提升 → 合法。
- ② `b + 1`：`explicit` 不能用于算术运算 → 报错。
- ③ `if (a)`：合法。
- ④ `if (b)`：条件位置允许 `explicit` → 合法。
- ⑤ `bool x = a;`：拷贝初始化，隐式转换 → 合法。
- ⑥ `bool y = b;`：拷贝初始化**不算**条件，`explicit` 转换不允许 → 报错。需改写为 `bool y(b);` 或 `bool y = static_cast<bool>(b);`。

`explicit operator bool` 是 C++11 引入的“safe bool idiom”官方替代，避免隐式 `bool` 被滥用为整数。
