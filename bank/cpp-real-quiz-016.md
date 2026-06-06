---
qid: cpp-real-quiz-016
type: single
kp: [cpp-cpp11, cpp-types]
primary_kp: cpp-cpp11
difficulty: hard
answer_key: B
tags: [interview-real, cppquiz, language-lawyer]
---
根据 C++17 标准，以下程序中 `a` 和 `b` 的类型分别是？

```cpp
auto a{1};
auto b = {1};
```

A. 都是 `int`
B. `a` 是 `int`，`b` 是 `std::initializer_list<int>`
C. 都是 `std::initializer_list<int>`
D. 编译错误

---

**解析：**

C++17 引入了 [dcl.spec.auto]/7 的规则**修正**：

- **direct-list-init**（无 `=`）`auto a{x};`：若 `{x}` 含**单个**元素，则 `a` 推导为元素的类型 `int`。
- **copy-list-init**（带 `=`）`auto b = {1};`：仍推导为 `std::initializer_list<T>`。

C++17 之前两者都推导为 `initializer_list`，但 Bjarne 等人觉得 `auto a{1}` 推成 list 太反直觉，于是 C++17 修正了 direct 形式。

很多教程没更新，仍说 `auto a{1}` 是 list，要小心。

**来源：** N3922；C++17 [dcl.spec.auto]/7

## Explanation

正确答案是 B。
C++17 引入了 [dcl.spec.auto]/7 的规则修正： direct-list-init（无 =）auto a{x};：若 {x} 含单个元素，则 a 推导为元素的类型 int。
copy-list-init（带 =）auto b = {1};：仍推导为 std::initializer_list<T>。
C++17 之前两者都推导为 initializer_list，但 Bjarne 等人觉得 auto a{1} 推成 list 太反直觉，于是 C++17 修正了 direct 形式。
