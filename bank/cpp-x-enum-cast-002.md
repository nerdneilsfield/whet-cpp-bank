---
qid: cpp-x-enum-cast-002
type: single
kp: [cpp-enum, cpp-casting]
primary_kp: cpp-casting
difficulty: medium
answer_key: C
---

下列 `switch` 语句，哪一个能编译通过？

```cpp
enum class State { Idle, Running, Stopped };

void handle1(State s) {
    switch (s) {
        case 0: break;                     // (A)
        case State::Idle: break;
    }
}

void handle2(int code) {
    switch (code) {
        case State::Running: break;        // (B)
    }
}

void handle3(State s) {
    switch (static_cast<int>(s)) {
        case 1: break;                     // (C)
    }
}

void handle4(State s) {
    switch (s) {
        case Idle: break;                  // (D) 没有 State:: 前缀
    }
}
```

A. handle1
B. handle2
C. handle3
D. handle4

---

**解析：**

`switch` 语句的规则是：`case` 标签的值类型必须与 `switch` 的表达式类型相同（或可以无歧义隐式转换）。`enum class` 没有到 `int` 的隐式转换，反之亦然，因此：

- **(A) handle1 错**：`switch (s)` 的表达式类型是 `State`，`case 0` 用整数字面量，没有从 `int` 到 `State` 的隐式转换。需要写成 `case State{0}` 或 `case static_cast<State>(0)`。
- **(B) handle2 错**：`switch (code)` 的表达式类型是 `int`，`case State::Running` 是 `State` 类型，反向没有隐式转换。需要 `case static_cast<int>(State::Running)`。
- **(C) handle3 对**：`switch (static_cast<int>(s))` 把表达式显式转为 `int`，`case 1` 是 `int`，类型匹配，**编译通过**。
- **(D) handle4 错**：`enum class` 的枚举值带作用域，必须用 `State::Idle`，不能直接 `Idle`。即使能找到名字 `Idle`，类型问题仍存在。

替代方案（C++20 起）：可以用 `using enum` 引入枚举值到当前作用域：

```cpp
void handle5(State s) {
    using enum State;        // C++20
    switch (s) {
        case Idle:    break; // 不再需要 State:: 前缀
        case Running: break;
        case Stopped: break;
    }
}
```

C++23 起 `std::to_underlying`、`std::is_scoped_enum_v` 等元函数让 enum class 操作更丰富，但隐式转换的禁止性是 enum class 的核心设计，不会被放开。