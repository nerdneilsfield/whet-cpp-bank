---
qid: cpp-opov-med-005
type: single
kp: [cpp-operator-overload]
difficulty: medium
answer_key: C
---

为下面的 `MyVec` 同时支持读写访问和只读访问，`operator[]` 应当如何重载？

```cpp
class MyVec {
    int data[16];
public:
    /*  ①  */ operator[](std::size_t i)       { return data[i]; }
    /*  ②  */ operator[](std::size_t i) const { return data[i]; }
};

void use(MyVec& v, const MyVec& cv) {
    v[0] = 42;          // 需要可写
    int x = cv[0];      // 只读
}
```

A. ① = `int`    ; ② = `int`
B. ① = `int`    ; ② = `int&`
C. ① = `int&`   ; ② = `int` 或 `const int&`
D. ① = `const int&` ; ② = `int&`

---

**解析：**

`operator[]` 通常重载成一对：非 const 版本返回引用以支持赋值，const 版本返回值或 const 引用用于只读。两者通过 `this` 的 cv 限定参与重载决议。

- 非 const 版本（`v[0]`）：返回 `int&`，这样 `v[0] = 42` 是把值写进 `data[0]`。如果返回 `int`，赋值的左侧是右值，编译报错。
- const 版本（`cv[0]`）：因为 `this` 是 `const MyVec*`，`data[i]` 实际上是 `const int`，所以返回 `int`（按值）或 `const int&` 都可以；返回 `int&` 会丢掉 const，编译失败。

因此 ① 必须是 `int&`，② 应是 `int`（小对象按值）或 `const int&`（大对象避免拷贝）。这一对重载是 STL 容器（如 `std::vector::operator[]`）的标准做法，让同一个容器既能在非 const 上下文写入，也能在 const 上下文安全读取。
