---
qid: cpp-real-nk-003
type: single
kp: [cpp-stl-basics, cpp-cpp11]
primary_kp: cpp-stl-basics
difficulty: medium
answer_key: A
tags: [interview-real, nowcoder]
---

```cpp
struct Foo {
    Foo(int x, double y) { /* ... */ }
    Foo(const Foo&) { std::cout << "copy"; }
    Foo(Foo&&) noexcept { std::cout << "move"; }
};

std::vector<Foo> v;
v.reserve(10);
```

以下哪条插入语句不会产生临时对象拷贝？

A. `v.emplace_back(1, 3.14);`
B. `v.push_back(Foo(1, 3.14));`
C. `v.push_back({1, 3.14});`
D. 所有语句都会产生至少一次临时对象

---

**解析：**

`emplace_back` 直接在 vector 的未初始化内存中构造对象，参数完美转发给 `Foo(int, double)` 构造函数，不存在临时对象。

`push_back(Foo(1, 3.14))` 和 `push_back({1, 3.14})` 都会先构造一个临时 `Foo`，然后 move（或 copy，若 noexcept 判定失败）进容器。

核心区别：emplace_back 的参数是构造参数，push_back 的参数是对象本身。对于可移动的简单类型，实测性能差异可能不大（编译器 RVO 优化），但语义不同。

**来源：** 牛客网 C++ STL 高频面试题 / Effective Modern C++ Item 42