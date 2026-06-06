---
qid: cpp-opov-r-001
type: single
kp: [cpp-operator-overload]
difficulty: easy
answer_key: "B"
---

### 题目

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

## Explanation

正确答案是 B，因为该选项对应 ``3 4 7`（`a` 和 `b` 不变，`c` 是新对象）`，符合题中代码或概念的 C++ 语义。运算符重载题要区分语法形式与实际调用的函数，并注意返回值、const、成员/非成员选择及内置运算符语义限制。常见误区是把重载看成改变了语言规则，或忽略临时对象、引用返回和左右操作数类型对重载解析的影响。 A 项、C 项、D 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
