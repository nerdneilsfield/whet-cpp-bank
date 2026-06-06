---
qid: cpp-tmpl-hard-001
type: single
kp: [cpp-templates]
difficulty: hard
answer_key: B
---

C++17 折叠表达式 `(... - args)` 与 `(args - ...)` 的求值方式有何区别？

```cpp
template<typename... Ts>
auto left(Ts... args)  { return (... - args); }
template<typename... Ts>
auto right(Ts... args) { return (args - ...); }

// left(1, 2, 3)  = ?
// right(1, 2, 3) = ?
```

A. 二者都是 `(1-2)-3 = -4`
B. `left(1,2,3) = (1-2)-3 = -4`（左折叠），`right(1,2,3) = 1-(2-3) = 2`（右折叠）
C. `left = 1-(2-3) = 2`，`right = (1-2)-3 = -4`
D. 折叠表达式只支持结合性运算符，`-` 不允许

## Explanation

C++17 折叠表达式语法：
- 一元左折叠：`(... op pack)` ⇒ `((p1 op p2) op p3) op ...` 即从左结合
- 一元右折叠：`(pack op ...)` ⇒ `p1 op (p2 op (p3 op ...))` 即从右结合
- 二元折叠：`(init op ... op pack)` 与 `(pack op ... op init)` 分别附加初值

`-` 是左结合的二元运算符（数学上），但折叠表达式语法本身决定结合方向。`left(1,2,3)` 是左折叠 `((1-2)-3) = -4`；`right(1,2,3)` 是右折叠 `1-(2-3) = 1-(-1) = 2`。对于满足结合律的运算（如 `+`、`*`），左右结果相同；但对 `-`、`/`、`%` 等不满足结合律的运算，方向决定结果。D 错：所有运算符都支持（包括 `,`、`&&`、`||`、`==` 等）。
