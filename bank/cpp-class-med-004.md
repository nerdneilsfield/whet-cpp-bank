---
qid: cpp-class-med-004
type: single
kp: [cpp-classes]
difficulty: medium
answer_key: C
---

下列代码中标记的 4 行，哪一行会编译失败？

```cpp
struct T {
    int          a;
    mutable int  b;
    int*         p;

    void f() const {
        a = 1;         // (1)
        b = 2;         // (2)
        *p = 3;        // (3)
        p = nullptr;   // (4)
    }
};
```

A. 仅 (1)
B. (1) 和 (3)
C. (1) 和 (4)
D. (1)、(3)、(4)

---

**解析：**

`const` 成员函数的隐式 `this` 类型是 `const T*`，因此通过 `this->` 访问的非 `mutable` 数据成员获得 `const` 限定，不能被赋值。

- (1) `a = 1`：`a` 是 `const int`（在该函数中），不能赋值 → 错。
- (2) `b = 2`：`b` 标记为 `mutable`，被显式排除在 const 之外，合法。
- (3) `*p = 3`：const 仅传递到指针本身（`int* const`），不传递到指针所指对象，因此 `*p` 仍是非 const `int`，合法。
- (4) `p = nullptr`：要修改指针本身，而指针在 const 函数中是 `int* const`，不能赋值 → 错。

逻辑上 const 成员函数只承诺"不修改对象的逻辑状态"，`mutable` 用于实现缓存/计数器等不影响逻辑状态的字段。
