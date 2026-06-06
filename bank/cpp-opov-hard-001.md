---
qid: cpp-opov-hard-001
type: single
kp: [cpp-operator-overload]
difficulty: hard
answer_key: C
---

C++20 引入 `operator<=>`（三向比较）。下列代码可以编译并比较吗？

```cpp
#include <compare>
struct Point {
    int x, y;
    auto operator<=>(const Point&) const = default;
};

Point a{1,2}, b{1,3};
bool r1 = (a < b);    // ①
bool r2 = (a == b);   // ②
```

A. ① 和 ② 都失败，因为只定义了 `<=>`
B. 只有 ① 成功，因为编译器从 `<=>` 自动合成所有关系运算符，但 `==` 必须显式定义
C. ① 和 ② 都成功：编译器从 default `<=>` 中合成 `<`/`<=`/`>`/`>=`；而 `==` 是**默认 `<=>` 时**也被同时隐式 default 化的特殊规则——`= default` 的 `<=>` 同时也声明了 `== / !=` 的默认成员
D. 必须改用 `std::strong_ordering` 才合法

## Explanation

C++20 三向比较的关键规则：
1. `= default` 的 `operator<=>` 会进行成员的字典序比较，返回类型为各成员 `<=>` 的公共类别（如全是 `int` → `strong_ordering`）。
2. 编译器从 `<=>` 自动**合成（rewrite）** `<`、`<=`、`>`、`>=` 四个运算符：`a < b` 重写为 `(a <=> b) < 0`。
3. `==` 和 `!=` 的处理特殊：**自定义 `<=>` 不自动产生 `==`**——但若 `<=>` 是 `= default` 的，那么 `operator==` 也被隐式声明并默认化（执行成员的逐字段 `==`）。所以本题中 ① 和 ② 都成功。
4. 若 `<=>` 是用户提供（不是 default），则必须手动声明 `operator==`（也可 `= default`）。

`strong_ordering` 是返回类型之一，无需手动指定。
