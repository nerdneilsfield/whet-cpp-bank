---
qid: cpp-mod-multi-med-005
type: multi
kp: [cpp-cpp14-17]
difficulty: medium
answer_key: [A, D]
---
关于 `if constexpr` 编译期条件分支，**哪些说法是正确的**？（多选）

```cpp
template <typename T>
auto length(const T& v) {
    if constexpr (requires { v.size(); }) {
        return v.size();
    } else {
        return sizeof(v);
    }
}
```

A. 当 `T = int` 时，`v.size()` 不会实例化，编译器只编译 `else` 分支
B. `if constexpr` 分支中未选中的代码**必须**对任意类型都合法编译
C. `if constexpr (false) { ... }` 的作用等价于 `if (false) { ... }`，只是风格差异
D. `if constexpr` 可用于非模板函数，但此时作用等同于普通 `if`（没有短路编译的效果）

---

**解析：**

A 正确：`if constexpr` 丢弃的分支（discarded branch）不会被实例化，这就是 SFINAE 之外进行类型分发的核心机制。
B 错误：丢弃分支中的代码**不需要**对当前类型合法。这是 `if constexpr` 与普通 `if` 的关键区别——普通 `if` 两个分支都会被实例化。
C 错误：在模板中 `if constexpr (false)` 的丢弃分支不会被实例化，而 `if (false)` 两个分支都会实例化。两者有本质区别。
D 正确：在非模板函数中 `if constexpr` 退化为普通 `if`，编译期没有短路效果，因为不需要处理模板实例化问题。

## Explanation

正确答案是 [A, D]。A 正确：`if constexpr` 丢弃的分支（discarded branch）不会被实例化，这就是 SFINAE 之外进行类型分发的核心机制。
D 正确：在非模板函数中 `if constexpr` 退化为普通 `if`，编译期没有短路效果，因为不需要处理模板实例化问题。
B 错误：丢弃分支中的代码不需要对当前类型合法。
