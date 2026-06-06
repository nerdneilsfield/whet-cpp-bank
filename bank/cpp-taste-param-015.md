---
qid: cpp-taste-param-015
type: single
kp: [cpp-lambdas, cpp-cpp14-17]
primary_kp: cpp-lambdas
difficulty: hard
answer_key: D
---

创建一个 lambda，让它捕获一个**不可拷贝**的 `std::unique_ptr<Widget>` 并在内部使用。从**参数传递品味**的角度，哪段最好？

```cpp
// A
auto cb = [&]() {
    w->do_something();
};
// w 作为被捕获的引用在外面存活
```

```cpp
// B
auto cb = [w = std::move(w)]() {
    w->do_something();
};
```

```cpp
// C
auto cb = [=]() {
    w->do_something();
};
```

```cpp
// D
auto cb = [w = std::make_unique<Widget>(/*...*/)]() {
    w->do_something();
};
// 或者在调用点转移所有权
```

A. A 段：`[&]` 延后捕获所有引用，最通用，lambda 拷贝无成本。
B. B 段：init-capture 把 `w` 移动进 lambda，lambda 活得比调用帧久也不怕。
C. C 段：`[=]` 按值捕获，语义明确。
D. D 段：init-capture 自构造或者从外部 move 进来，lambda 拥有所有权。

## Explanation

正确答案是 **D**。

- **A 段（差）**：`[&]` 捕获引用，lambda 生命周期不能比外部帧长——一旦 lambda 被异步调度、投递到线程池或跨续传，`w` 可能已经销毁或离开作用域，成为悬空引用。这种 "dangling by reference capture" 是最常见的 C++ lambda bug 之一（Clang-tidy 的 `clang-analyzer-cplusplus.InnerPointer` 检查专门抓这个）。
- **B 段（差）**：`[w = std::move(w)]()` 有命名歧义——被捕获的 `w` 是 lambda 副本的成员，外部 `w` 已经被 move 走（变成 null）。如果在 lambda 定义之后 lambda 之外的代码还想用原 `w`，就会误触空指针。名称遮挡让代码难以阅读和重构。而且 capture 后的名字和外部变量完全相同，Clang-tidy 会有警告 `hicpp-no-array-decay, readability-identifier-naming` 相关潜在混淆。
- **C 段（错）**：`[=]` 会尝试拷贝捕获，但 `unique_ptr` 不可拷贝——直接编译错误：`call to implicitly-deleted copy constructor`. 这不是品味问题，是语法错误。
- **D 段（好）**：C++14 的 init-capture（广义捕获）允许用任意表达式初始化 lambda 内的 capture 副本。`[w = std::make_unique<Widget>(...)]` 在捕获点构造 `Widget`，`w` 名 lambda 唯一拥有；或者在外部 move 过来 `auto cb = [w = std::move(w)]() {...}` 但需要注意原变量名称遮挡问题——这里最好显式换名字（`[widget = std::move(w)]()`）。D 的方案因为可以自构造 `make_unique` 规避了原变量名遮挡。

**核心识别点：**
- 不可拷贝的移动语义对象进入 lambda → 用 C++14 init-capture：
  `[guard = std::make_unique<Guard>()]()`。
- `[&]` 捕获引用 + 异步调度 = 悬空引用，常见的 latent bug。
- `[=]` 对 `unique_ptr` 编译错误，因为它尝试拷贝；用 `std::move` 通过编译但名字遮挡混淆，最好 rename。
- init-capture 明确的 capture 变量名字和初始化表达式，让 lambda 的"拥有的资源"一目了然。

**来源：** C++14 标准 [expr.prim.lambda]；Effective Modern C++ Item 32；C++ Core Guidelines F.52（"Prefer init-capture to move-in-default-capture"）；clang-tidy 的 `clang-analyzer-cplusplus.InnerPointer`。
