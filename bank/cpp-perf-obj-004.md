---
qid: cpp-perf-obj-004
type: single
kp: [cpp-move-semantics, cpp-functions]
primary_kp: cpp-move-semantics
difficulty: hard
answer_key: C
tags: [performance, code-taste]
---

要写一个函数返回一个大 `std::vector<double>`。下面四个写法功能等价，哪个最值得采用？

```cpp
// A
std::vector<double> make_data(std::size_t n) {
    std::vector<double> result(n);
    for (std::size_t i = 0; i < n; ++i) result[i] = i * 0.1;
    return std::move(result);
}

// B
std::vector<double> make_data(std::size_t n) {
    std::vector<double> result(n);
    for (std::size_t i = 0; i < n; ++i) result[i] = i * 0.1;
    return result;
}

// C
void make_data(std::size_t n, std::vector<double>& out) {
    out.resize(n);
    for (std::size_t i = 0; i < n; ++i) out[i] = i * 0.1;
}

// D
std::vector<double>* make_data(std::size_t n) {
    auto* result = new std::vector<double>(n);
    for (std::size_t i = 0; i < n; ++i) (*result)[i] = i * 0.1;
    return result;
}
```

A. A — 显式 std::move 确保走移动而非拷贝
B. B — 直接 return 命名局部变量，让编译器自己优化
C. C — 传入输出参数，避免任何返回值开销
D. D — 用裸指针返回，调用方负责 delete

---

**解析：**

选 B（NRVO 直接零拷贝零移动）；C 是错误诱导项。这道题考的是"NRVO（命名返回值优化）vs 显式 move vs 输出参数"的微妙差异。

逐一品味：

- **A**：**`return std::move(result)` 抑制 NRVO/RVO**！编译器看到 `std::move(result)` 是一个 xvalue 表达式（不再是命名局部变量），无法识别为 NRVO 候选——只能做一次 move 构造。move 一个 vector 是字段 swap（3 个 8 字节字段），便宜但不是零。比 B 慢一次 move。这是 *Effective Modern C++* Item 25 反复警告的"对返回值用 std::move 是反优化"。
- **B**：编译器对 `return result;` 这种 named return 应用 **NRVO**：直接在调用者的返回值槽内构造 result——**零拷贝、零移动**。`make_data` 返回时，调用方拿到的 vector 就是函数里那个对象本身。这是 C++17 起 mandatory copy elision 不完全覆盖 NRVO（NRVO 仍是可选的），但所有主流编译器在 `-O1` 起都做。**最佳**。
- **C**：传出参数看似"避免返回值开销"——但 ① 接口丑（不能链式 `auto v = make_data(...)`）；② `out.resize(n)` 在 out 之前已经有内容时会扔掉旧内容、可能不重分配（如果 capacity 够），看似省一次分配；但若调用者每次传新的空 vector，**和 B 完全一样**（NRVO 后没有额外开销可省）；③ 现在的"省一次构造"在 B 的 NRVO 后并不存在——B 已经是零拷贝。C 是为了解决一个**不存在的问题**牺牲接口。C++ Core Guidelines F.20: "For 'out' output values, prefer return values to output parameters"。
- **D**：返回裸指针让调用方手动 `delete`——回到 1990 年代 C++。多一次堆分配 sizeof(vector)，调用方忘记 delete 就泄露。即使用 `unique_ptr<vector<double>>` 接住也是多一层间接 + 一次额外堆分配。比 B 慢且不安全。

**核心识别点：**
- 看见 `return std::move(local)` → 警觉这是反优化，抑制了 NRVO
- 看见为了性能而写"输出参数"接口 → 警觉是不是在解决一个 NRVO 已经解决的问题
- NRVO 是编译器把"局部变量构造在返回值槽里"的优化——零拷贝零移动
- 直接 `return local;` 是现代 C++ 返回大对象的正确姿势
- `return std::move(x)` 仅在 x 不是函数局部变量（如成员、参数）时才有意义

**来源：** Scott Meyers, "Effective Modern C++", Item 25 "Use std::move on rvalue references, std::forward on universal references" + Item 36 "Use std::launch::async"；C++17 标准 [class.copy.elision]；C++ Core Guidelines F.20.

## Explanation

选 B，因为直接 `return result;` 允许 NRVO，在调用者返回值槽中构造对象，通常零拷贝零移动。`return std::move(result)` 会破坏 NRVO 候选，反而强制至少一次移动；输出参数也没有性能优势且接口更差。误区是把显式 move 当成返回局部变量的优化。
