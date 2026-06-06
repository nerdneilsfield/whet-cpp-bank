---
qid: cpp-tmp-med-004
type: single
kp: [cpp-templates]
difficulty: medium
answer_key: C
---

给定以下三个模板定义，`Foo<int*>` 实例化时匹配哪个版本？

```cpp
// (1) 主模板
template<typename T>
struct Foo { static constexpr int id = 0; };

// (2) 指针偏特化
template<typename T>
struct Foo<T*> { static constexpr int id = 1; };

// (3) int 全特化
template<>
struct Foo<int> { static constexpr int id = 2; };
```

A. 主模板（id = 0）
B. `int` 全特化（id = 2）
C. 指针偏特化（id = 1）
D. 编译错误，存在歧义

---

**解析：**

`Foo<int*>`：模板实参是 `int*`（指针类型）。

- 主模板：可匹配（T = int*），id = 0。
- 指针偏特化 `Foo<T*>`：T = int，可匹配，id = 1。
- `int` 全特化 `Foo<int>`：实参必须精确为 `int`，不匹配 `int*`。

候选只有主模板和指针偏特化，偏特化更特化，故选 **(C) id = 1**。

注意：若实参是 `Foo<int>`，才会匹配全特化（id = 2）。
