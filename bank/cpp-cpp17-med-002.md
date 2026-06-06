---
qid: cpp-cpp17-med-002
type: single
kp: [cpp-cpp14-17]
difficulty: medium
answer_key: A
---

C++17 `if constexpr` 的 discarded branch 仍需满足基本语法正确性。以下哪段代码会编译失败？

A.
```cpp
template<typename T>
void f(T v) {
    if constexpr (std::is_same_v<T, int>) {
        std::cout << v;
    } else {
        v.size();  // 对 int 调用 .size()
    }
}
int main() { f(42); }
```

B.
```cpp
template<typename T>
void g(T v) {
    if constexpr (std::is_same_v<T, int>) {
        return v + 1;
    } else {
        return v.size();
    }
}
int main() { g(42); }
```

C.
```cpp
template<typename T>
void h(T v) {
    if constexpr (std::is_same_v<T, int>) {
        (void)v;
    }
    static_assert(std::is_same_v<T, double>, "must be double");
}
int main() { h(42); }
```

D.
```cpp
template<typename T>
auto k(T v) {
    if constexpr (std::is_same_v<T, int>) {
        return v * 2;
    } else {
        return 0.0;
    }
}
int main() { k(42); }
```

---

**解析：**

`if constexpr` 的 discarded branch（不满足条件的分支）不会被实例化，但**仍需满足语法正确性和名字查找的基本原则**。A 选项中 `v.size()` 对 `int` 完全不合法（语法错误），不是因为实例化而报错——它会直接被编译器标记为语法无效。

B 和 D 的 discarded branch 在实例化时被丢弃，不产生编译错误。C 中的 `static_assert` 在 if constexpr 外部，必然触发。

核心规则：discarded branch **不参与模板实例化**，但**必须语法合法且名字查找成功**。

## 解析

正确答案是 A。`auto` 按模板实参推导规则工作，常会丢弃顶层 `const` 和引用，除非显式写成 `auto&`。选项 A 的表述“｀｀｀cpp template<typename T> void f(T v) { if constexpr (std::is_same_v<T, int>) { std::cout << v; } else { v.size(); // 对 int 调用 .size() } } int main() { f(42); } ｀｀｀”正好符合该规则。B、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
