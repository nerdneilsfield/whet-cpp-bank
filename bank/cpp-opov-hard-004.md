---
qid: cpp-opov-hard-004
type: single
kp: [cpp-operator-overload]
difficulty: hard
answer_key: D
---

观察以下代码：

```cpp
struct Money {
    double amount;
    operator double() const { return amount; }
    Money operator+(const Money& o) const { return {amount + o.amount}; }
};

Money m1{100.0}, m2{50.0};
auto r1 = m1 + m2;      // ①
auto r2 = m1 + 5.0;     // ②
auto r3 = 5.0 + m1;     // ③
```

哪一行可能引发歧义或意外？

A. ① 调用 `Money::operator+`，返回 `Money`
B. ② 调用 `Money::operator+`，5.0 隐式转换为 `Money`？编译失败
C. ③ 调用全局 `operator+(double, double)`，`m1` 转换为 `double`，返回 `double`
D. ① 正确；② 编译失败或歧义：`m1+5.0` 既可经 `Money::operator+`（5.0→`Money` 但没有 `Money(double)` 单参数构造则不行）也可经 `m1` 转 `double` 再 `+5.0`（返回 `double`）——若提供了 `Money(double)` 构造，则两路径都成立产生歧义；③ 通常调用 `double+double`（`m1` 转 `double`），但若 `Money` 有非 `explicit` 单参数构造也可能歧义

## Explanation

这是经典"隐式转换 + 重载运算符 → 歧义"的多对一陷阱。`Money` 既能 `→ double`（转换运算符）又可能 `double → Money`（如果有非 explicit 构造），运算符重载与内置运算符同时成为候选。

具体分析：
- ① 两个 `Money` → `Money::operator+`，明确。
- ② `m1 + 5.0`：候选包括 `Money::operator+(Money)`（需 5.0→Money，要求 `Money(double)` 非 explicit）与内置 `double+double`（`m1`→double）。若 `Money(double)` 存在则歧义；若不存在，则只剩内置 `double+double`，返回 `double`（不再是 `Money`，可能不是期望）。
- ③ 类似 ②，但左侧是 `double`，候选为内置 `double+double` 和 `Money::operator+`（要求 5.0→Money）。

建议：转换运算符标记 `explicit`，单参数构造标记 `explicit`，避免双向隐式转换；或为 `Money` 提供完整的混合类型 `operator+(Money, double)` 等显式重载。
