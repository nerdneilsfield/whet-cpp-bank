---
qid: cpp-move-semantics-multi-hard-004
type: multi
kp: [cpp-move-semantics]
difficulty: hard
answer_key: [A, B, C]
---
关于 C++17 强制拷贝省略（mandatory copy elision），以下说法正确的是哪些？

```cpp
struct S {
    S() = default;
    S(const S&) = delete;
    S(S&&) = delete;
};

S make() { return S{}; }         // (1) C++17 合法吗？
S f(bool b) {                    // (2)
    S a, b;
    return b ? a : b;            // C++17 & C++14 行为？
}

void g(S);                       // (3)
g(S{});
```

A. (1) 在 C++17 下合法：`return S{};` 触发 mandatory copy elision，即使拷贝/移动构造都已 delete，也不会生成临时对象。
B. (2) 在 C++17 下仍可能需要拷贝或移动——因为条件表达式 `b ? a : b` 需要对 `a` 和 `b` 之一做拷贝，不是 prvalue 上下文。
C. (3) `g(S{})` 中 `S{}` 作为 prvalue 直接构造到函数参数位置，C++17 起完全避免临时对象。
D. C++17 的 mandatory copy elision 对 NRVO（具名返回值优化）也适用——编译器在 C++17 后不需要检查拷贝/移动的可访问性。

---

**解析：**

A 正确：`return S{};` 中的 `S{}` 是 prvalue，在 C++17 下直接构造到返回值位置，不会为 prvalue 创建临时对象，因此不需要拷贝/移动构造可访问。
B 正确：三元条件表达式中的局部变量是左值而非 prvalue，所以即使 C++17，`return b ? a : b` 也需要将 a 或 b 拷出——此时若拷贝构造已 delete 则报错。这也是编译器能做的 elision 与 mandatory elision 之间最重要的区别。
C 正确：C++17 规范规定 prvalue（如 `S{}`）在初始化场景中直接 materialize 到目标位置，不做附加临时对象，这是 mandatory elision 的核心机制。
D 错误：NRVO 在 C++17 中仍然是可选的（non-mandatory）优化，标准不要求它，编译器实现受 QoI 控制。若拷贝/移动构造被 delete，NRVO 不行时会报错。只有 `return 纯右值表达式;` 才是 mandatory 的。

## Explanation

A、B、C 正确：C++17 中 prvalue 可直接构造到目标位置，`return S{}` 和 `g(S{})` 不需要可用的拷贝/移动构造。具名局部变量或条件表达式不是同一种 mandatory copy elision 场景，仍可能需要拷贝或移动。常见误区是认为 C++17 后所有返回值优化都强制发生；NRVO 仍是可选优化。
