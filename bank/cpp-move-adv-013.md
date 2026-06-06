---
qid: cpp-move-adv-013
type: single
kp: [cpp-move-semantics]
difficulty: hard
answer_key: B
---

关于 `auto&&`，下列说法**正确**的是？

```cpp
int x = 10;
auto&& a = x;       // (1)
auto&& b = 42;      // (2)
auto&& c = std::move(x);  // (3)
```

A. (1)(2)(3) 中 `auto&&` 均是右值引用，因为带有 `&&`
B. `auto&&` 是转发引用，(1) 绑定左值推导为 `int&`，(2) 绑定右值推导为 `int`（`b` 类型为 `int&&`），(3) 绑定右值推导为 `int`（`c` 类型为 `int&&`）
C. `auto&&` 只能绑定右值，(1) 会编译失败
D. `auto&&` 等价于 `const auto&`，能绑定任意值但不可修改

---

**解析：**

`auto&&` 中的 `auto` 充当模板参数，`&&` 使其成为**转发引用**，可绑定任意值类别：

| 表达式             | 推导 auto= | `a/b/c` 类型 |
|--------------------|------------|--------------|
| `x`（左值 int）    | `int&`     | `int&`（折叠 `int& &&` → `int&`） |
| `42`（右值 int）   | `int`      | `int&&` |
| `std::move(x)`（右值 int） | `int` | `int&&` |

选 B。`auto&&` 在范围 for 循环（`for (auto&& e : range)`）里很常见，能以最小开销绑定任意元素类型。
