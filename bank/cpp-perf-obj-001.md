---
qid: cpp-perf-obj-001
type: single
kp: [cpp-stl-basics, cpp-move-semantics]
primary_kp: cpp-stl-basics
difficulty: hard
answer_key: A
tags: [performance, code-taste]
---

要把 100 万个 `std::pair<std::string, int>` 加到 vector 里，string 通过函数生成。下面四个写法功能等价，哪个最值得采用？

```cpp
// A
std::vector<std::pair<std::string, int>> v;
v.reserve(1'000'000);
for (int i = 0; i < 1'000'000; ++i)
    v.emplace_back(make_name(i), i);

// B
std::vector<std::pair<std::string, int>> v;
v.reserve(1'000'000);
for (int i = 0; i < 1'000'000; ++i)
    v.push_back(std::pair<std::string,int>(make_name(i), i));

// C
std::vector<std::pair<std::string, int>> v;
v.reserve(1'000'000);
for (int i = 0; i < 1'000'000; ++i) {
    auto p = std::pair<std::string,int>(make_name(i), i);
    v.push_back(std::move(p));
}

// D
std::vector<std::pair<std::string, int>> v;
v.reserve(1'000'000);
for (int i = 0; i < 1'000'000; ++i)
    v.push_back({make_name(i), i});
```

A. A — emplace_back 用参数列表直接在容器槽里构造
B. B — push_back 接收显式构造的 pair 临时对象
C. C — 把临时 pair 存局部变量，再 move 进容器
D. D — push_back + brace-init，让编译器推导类型

---

**解析：**

选 A。这道题考的是"emplace 跳过临时对象、push_back+花括号触发隐式 pair 构造"两层差异。

逐一品味：

- **A**：`emplace_back(make_name(i), i)` 完美转发参数到 vector 槽内的 `pair` 构造函数——**零次临时对象、零次拷贝/移动**。`make_name(i)` 返回的 string 直接 move-construct 到 pair 的 string 成员里。生成代码 = 1 次 string 构造 + 1 次 int 拷贝。
- **B**：`std::pair<string,int>(make_name(i), i)` 先构造一个临时 pair（string 在临时 pair 里 move 一次），再 `push_back(临时)` 触发一次 move（string 再 move 一次进 vector 槽）。**比 A 多一次 string move**。string 的 move 操作虽然是 O(1)（交换指针 + size + capacity），但仍要写 3 个 8 字节字段；100 万次累计可见。约比 A 慢 **10–30%**。
- **C**：和 B 几乎一样，把临时显式命名为 `p`，再 `std::move(p)`。语义和 B 等价（事实上 B 里编译器可能能做 copy elision，但 C 因为有命名变量、是 lvalue，需要显式 move）。多了变量构造析构。**比 B 略慢**或等同。
- **D**：`push_back({make_name(i), i})` 用 brace-init 让编译器推导构造一个 pair 临时再 push。看起来比 B 简洁，但**生成代码和 B 等价**：先临时 pair、再 move 进 vector。比 A 多一次 string move。看似现代，实则不如 A 直接 emplace。

A 的核心优势是 *in-place construction*：`emplace_back` 直接把参数转发给 vector 内部的 `allocator.construct()`，**没有"先在外面构造再 move 进来"的两步**。对持有堆资源的元素（string、vector、map 等），这一次省下的 move 就是最大的常数项。

**核心识别点：**
- 看见 `push_back(T(args...))` 或 `push_back({args...})` → 警觉是不是写成了"先建临时再 push"，可以直接 emplace
- 看见 `move(local_var)` 后接 push → 警觉 local_var 是不是本来就不必存在
- emplace 对**简单类型**（int, double, trivially copyable）和 push 等价，但对**持有资源的类型**（string、vector、unique_ptr）能省 1 次 move
- 在循环里**100 万次 × 1 次 move = 数百万次 8 字节字段写**，看似小但摆在 cache 紧张时是 5–10% 的差距
- `reserve` 必须配合 emplace/push 才发挥作用——没 reserve 时再多 emplace 也跑不掉重分配

**来源：** Scott Meyers, "Effective Modern C++", Item 42 "Consider emplacement instead of insertion"；Herb Sutter, "back to the basics", CppCon 2014；C++ Core Guidelines C.137.
