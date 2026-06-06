---
qid: cpp-taste-init-008
type: single
kp: [cpp-lambdas, cpp-undefined-behavior]
primary_kp: cpp-lambdas
difficulty: hard
answer_key: D
tags: [code-taste, best-practice, lambda-capture, lifetime]
---
要把一段计算包装成 `std::function<int()>` 存到容器里，以便**稍后**（可能在另一个线程、可能在原函数返回之后）调用。计算依赖一个 `std::string prefix`（在当前函数里临时算出来的）。四种 lambda 写法哪个最有品味？

```cpp
// A
auto make_task() {
    std::string prefix = compute_prefix();
    return std::function<int()>([&]{ return (int)prefix.size(); });
}

// B
auto make_task() {
    std::string prefix = compute_prefix();
    return std::function<int()>([&prefix]{ return (int)prefix.size(); });
}

// C
auto make_task() {
    std::string prefix = compute_prefix();
    return std::function<int()>([=]{ return (int)prefix.size(); });
}

// D
auto make_task() {
    std::string prefix = compute_prefix();
    return std::function<int()>([p = std::move(prefix)]{ return (int)p.size(); });
}
```

A. A — `[&]` 默认按引用最简洁
B. B — 显式按引用捕获 `prefix`，比 A 更精确
C. C — `[=]` 按值捕获保证生命周期安全
D. D — init-capture 把 `prefix` move 进 lambda，零拷贝且无悬空

---

**解析：**

选 D。这道题考 **"lambda 离开当前作用域时，捕获变量的生命周期"** ——A、B、C 各踩一个坑，D 是 C++14 的正解。

逐一品味：

- **A** `[&]` ：**悬空引用**。`prefix` 是 `make_task` 的局部变量，函数一返回它就被销毁。lambda 把它按引用捕获，存到 `std::function` 里运回去——调用方一执行 lambda 就读已销毁对象的内存。**未定义行为**。`[&]` 的"简洁"是地雷：它捕获**所有**被用到的变量按引用，包括明明应该按值的。Scott Meyers Item 31 标题直接叫 "Avoid default capture modes"。
- **B** `[&prefix]` ：**同样悬空**——只是把雷标出来了。"显式"不改变引用的本质，只让 review 时更容易看见这是引用捕获。问题没解决。看到 lambda 要逃出当前作用域、还有引用捕获 → 立刻警觉。
- **C** `[=]` ：**安全但低效**。`[=]` 把 `prefix` 按值**拷贝**进 lambda——对 `std::string` 是一次堆分配 + memcpy。`prefix` 是局部变量，函数返回后我们其实**不再需要它**，按值拷贝是把"本来要扔掉的东西"复印一份带走，浪费。同样 `[=]` 是默认捕获，会无差别拷贝所有被用到的变量（如果还有 `std::vector<...>` 之类的就更贵）。
- **D** `[p = std::move(prefix)]` ：**C++14 init-capture**（也叫 generalized lambda capture）。它做了三件正确的事：
  1. **Move 而不是 copy**：`prefix` 反正要在函数返回时被销毁，把它的内容直接 move 进 lambda 的成员变量 `p`，零堆分配。
  2. **lambda 拥有 `p` 的生命周期**：`p` 是 lambda 闭包对象的成员，闭包活多久 `p` 就活多久——闭包被存进 `std::function` 跑到任何地方，`p` 跟着走，无悬空。
  3. **显式命名 `p`**：不是默认捕获，review 时能精确看到 lambda 抓走了什么。

`[p = std::move(prefix)]` 这个语法的"等号"不是赋值——它声明并初始化一个 lambda 的成员变量 `p`，初值是 `std::move(prefix)`。语法上等价于"把闭包当成一个匿名 class，给它写一个成员 `p`，构造函数从外面 move 一个值进来"。C++14 之前**无法表达** move-only 类型的捕获（unique_ptr 在 C++11 lambda 里捕不进去），init-capture 就是为此引入。

**核心识别点**：

- lambda 会**逃出当前作用域**（存到 `std::function`、扔进线程、返回出去、放进容器）→ **绝不**用 `[&]` / `[&x]`
- lambda 不会逃出（立刻消费——`std::sort` 的比较器、`std::for_each` 的 body）→ `[&]` 安全且零开销，可以用
- 看见 `[=]` 在 lambda 体里 → 想想是不是有大对象被无意拷贝
- 看见 `[var = std::move(var)]` → 知道这是 C++14 init-capture，目的通常是 **move 一个 move-only 对象**或**避免拷贝重对象**
- 默认捕获 `[&]` / `[=]` 在 C++ Core Guidelines (F.54) 中被建议**避免**——总是显式列出捕获

`std::function` 的存在让 lambda 的生命周期问题被放大——只要你看到 lambda 进入 `std::function`、`std::any`、容器、`std::async`、线程、协程，立刻按"逃出当前作用域"处理。

**来源：** 手写题。init-capture 见 ISO/IEC 14882:2014 §5.1.2 [expr.prim.lambda]/14；最佳实践见 Scott Meyers *Effective Modern C++* Item 31 "Avoid default capture modes"、Item 32 "Use init capture to move objects into closures"；C++ Core Guidelines F.54。
