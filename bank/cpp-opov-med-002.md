---
qid: cpp-opov-med-002
type: single
kp: [cpp-operator-overload]
difficulty: medium
answer_key: B
---

下列 `operator<<` 的重载方式，哪一个能让 `std::cout << p << "\n"` 正确编译并支持链式输出？

```cpp
struct Point { int x, y; };
```

A. 作为 `Point` 的成员函数：`std::ostream& Point::operator<<(std::ostream& os) const;`
B. 作为非成员函数：`std::ostream& operator<<(std::ostream& os, const Point& p);`
C. 作为 `std::ostream` 的成员函数（不可能修改 std 类型，但假设可以）
D. 作为非成员函数：`Point operator<<(const Point& p, std::ostream& os);`

---

**解析：**

`operator<<` 必须实现成**非成员函数**，并且第一个参数是 `std::ostream&`，第二个参数是被输出的类型。这是因为成员函数版本要求左操作数是“当前类型”的对象，而 `cout << p` 的左操作数是 `std::ostream`——我们无权给 `std::ostream` 添加成员函数。

返回 `std::ostream&` 是为了支持链式：`cout << p << "\n"` 会被解析为 `((cout << p) << "\n")`，第一步必须返回 `cout` 本身才能让第二步继续工作。

B 是正确签名，通常写成：

```cpp
std::ostream& operator<<(std::ostream& os, const Point& p) {
    return os << '(' << p.x << ',' << p.y << ')';
}
```

如果该函数需要访问私有成员，可以在 `Point` 内声明为 `friend`，但函数本身仍是非成员。
