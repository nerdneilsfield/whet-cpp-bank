---
qid: cpp-move-adv-009
type: single
kp: [cpp-move-semantics]
difficulty: medium
answer_key: C
---

以下代码中，`bar` 函数接收 `s`（一个 `std::string` 左值）和 `42`（右值），分别判断形参 `x` 的最终类型：

```cpp
template<typename T>
void bar(T&& x) { /* ... */ }

std::string s = "hello";
bar(s);    // 调用 (1)：T 推导为 std::string&，x 的类型？
bar(42);   // 调用 (2)：T 推导为 int，x 的类型？
```

A. (1) `std::string&&`；(2) `int&`
B. (1) `std::string&`；(2) `int&`
C. (1) `std::string&`；(2) `int&&`
D. (1) `std::string&&`；(2) `int&&`

---

**解析：**

(1) 传入左值 `s`（类型 `std::string`）：
- T 推导为 `std::string&`
- `T&&` = `std::string& &&` → 折叠为 `std::string&`（左值引用）

(2) 传入右值 `42`（类型 `int`）：
- T 推导为 `int`
- `T&&` = `int&&`（右值引用，无需折叠）

选 C。

## 解析

正确答案是 C，传入左值 `s` 时 `T` 推导为 `std::string&`，形参折叠为 `std::string&`。传入右值 `42` 时 `T=int`，形参为 `int&&`。关键误区是忽略具名左值和临时右值会导致不同的模板参数推导。 这类题的关键是区分语法形式、对象生命周期和所有权语义：语法看似相近时，应先判断谁拥有资源、表达式值类别是什么，以及标准是否保证该行为；不要根据实现习惯或表面写法推断答案。
