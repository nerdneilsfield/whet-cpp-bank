---
qid: cpp-opov-r-001
type: single
kp: [cpp-operator-overload]
difficulty: easy
answer_key: "B"
---

## 题目

阅读以下代码，执行后 `a`、`b`、`c` 的值分别是什么？

```cpp
#include <iostream>

struct Vec {
    int x;
    Vec(int x) : x(x) {}
    Vec operator+(const Vec& rhs) const {
        return Vec(x + rhs.x);
    }
};

int main() {
    Vec a(3), b(4);
    Vec c = a + b;
    std::cout << a.x << " " << b.x << " " << c.x << "\n";
}
```

A. `7 4 7`（`a` 被修改为 7）
B. `3 4 7`（`a` 和 `b` 不变，`c` 是新对象）
C. `3 4 3`（`+` 返回左操作数的副本）
D. 编译错误，`operator+` 需要声明为 `friend`

## 解析

`operator+` 返回新构造的 `Vec` 对象，不修改 `a` 或 `b`。`a.x` 仍为 3，`b.x` 仍为 4，`c.x` 为 7。这是运算符重载的标准惯用法：算术运算符应返回新值而非修改操作数。
