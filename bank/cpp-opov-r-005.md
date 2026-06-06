---
qid: cpp-opov-r-005
type: single
kp: [cpp-operator-overload]
difficulty: easy
answer_key: "B"
---

## 题目

以下代码能否编译？如果不能，原因是什么？

```cpp
struct Score {
    int value;
    Score(int v) : value(v) {}

    bool operator==(const Score& rhs) const {
        return value == rhs.value;
    }
    // 未定义 operator!=
};

int main() {
    Score a(90), b(80);
    bool result = (a != b);   // 使用 !=
}
```

A. 编译通过，编译器自动从 `operator==` 推导出 `operator!=`
B. 编译错误（C++17 及之前）：`operator!=` 未定义，无法使用 `!=`
C. 编译通过，`!=` 默认等于 `!(a == b)`，无需额外定义
D. 运行时错误，`!=` 比较的是指针地址

## 解析

在 **C++20 之前**，定义了 `operator==` 并不会自动提供 `operator!=`；必须显式定义。`a != b` 在 C++17 及更早标准下会导致编译错误（no match for `operator!=`）。C++20 引入了"对称比较"规则，此时编译器可以将 `a != b` 重写为 `!(a == b)`，但 C++20 之前不适用。
