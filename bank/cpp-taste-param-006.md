---
qid: cpp-taste-param-006
type: single
kp: [cpp-lambdas, cpp-templates]
primary_kp: cpp-lambdas
difficulty: hard
answer_key: D
---

`for_each_node` 想对一棵树的每个节点调用用户传入的回调，回调被调用次数极多（百万级）。从**参数传递品味**的角度，哪段最合适？

```cpp
// A
void for_each_node(Node* root, std::function<void(Node*)> f) {
    if (!root) return;
    f(root);
    for (auto* c : root->children) for_each_node(c, f);
}
```

```cpp
// B
void for_each_node(Node* root, void (*f)(Node*)) {
    if (!root) return;
    f(root);
    for (auto* c : root->children) for_each_node(c, f);
}
```

```cpp
// C
template <class F>
void for_each_node(Node* root, const F& f) {
    if (!root) return;
    f(root);
    for (auto* c : root->children) for_each_node(c, f);
}
```

```cpp
// D
template <class F>
void for_each_node(Node* root, F&& f) {
    if (!root) return;
    f(root);
    for (auto* c : root->children) for_each_node(c, std::forward<F>(f));
}
```

A. A 段：`std::function` 类型擦除最灵活，能接受任何 callable，签名干净。
B. B 段：函数指针最轻量，没有任何类型擦除开销。
C. C 段：模板 + `const&` 既零开销又能接 lambda、仿函数、函数指针。
D. D 段：模板 + 万能引用，可接任何 callable、支持有状态可变 lambda，且零开销。

## 解析

正确答案是 **D**。

- **A 段（差）**：`std::function` 是类型擦除，每次调用要走一次虚表式的间接调用；有状态 lambda 还可能触发堆分配。在百万级调用的回调点上，是性能洼地。签名干净的代价是 10× 的延迟。
- **B 段（差）**：函数指针接不了有捕获的 lambda（`[&counter](Node*){...}`），调用方被迫退化成全局函数或仿函数；签名虽轻，灵活性骤降，常见模式直接用不了。
- **C 段（差）**：`const F&` 拒绝调用**带状态的可变 lambda**（`mutable`），因为 `const` 仿函数的 `operator()` 是 const 版；常见的"累加计数 lambda" 直接编译失败。性能上倒是零开销，但适用面比 D 窄。
- **D 段（好）**：模板 + 万能引用是 STL 算法的通用范式（`std::for_each`、`std::sort` 的比较器都是这么传）。能接任何 callable（lambda、函数指针、仿函数、`std::function`），调用是直接调用、可内联，零开销；既不挡可变 lambda，也不强迫调用方写 `std::ref`。

**核心识别点：**
- 热路径上的回调用模板 + 万能引用，不要 `std::function`。
- `std::function` 适合"需要在容器里存异构 callable" 或"跨编译单元的事件总线"，不适合算法回调。
- `const F&` 会拒绝 mutable lambda，是常见的隐形约束。
- 模板回调的代价是头文件依赖；这是性能与编译期模块化的权衡。

**来源：** Effective STL Item 38；Effective Modern C++ Item 34；`std::for_each` 实现；CppCon "Type Erasure" 系列。
