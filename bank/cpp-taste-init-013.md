---
qid: cpp-taste-init-013
type: single
kp: [cpp-cpp11, cpp-undefined-behavior]
primary_kp: cpp-cpp11
difficulty: hard
answer_key: A
tags: [code-taste, best-practice, lifetime-extension, temporaries]
---
要从函数返回的临时 `std::string` 里取一个字段。返回值不会被修改，且要在多次操作里复用。四种写法哪个最有品味？

```cpp
// A
const std::string& s = make_long_string();  // 返回的是 std::string 值
do_one(s);
do_two(s);
do_three(s);

// B
auto& s = make_long_string();
do_one(s);
do_two(s);
do_three(s);

// C
std::string&& s = make_long_string();
do_one(s);
do_two(s);
do_three(s);

// D
std::string s = make_long_string();
do_one(s);
do_two(s);
do_three(s);
```

A. A — `const T&` 把临时对象的生命周期延长到引用的作用域，无拷贝
B. B — `auto&` 是非 const 引用，更灵活
C. C — `T&&` rvalue 引用直接绑定到临时，最现代
D. D — 直接按值接，最直观

---

**解析：**

选 A。这道题考 **"绑定到 `const T&` 的临时对象，生命周期延长到引用的作用域"** —— 这是 C++ 一条非常特殊的规则，而 `auto&` 和 `T&&` 的行为微妙不同。

逐一品味：

- **A** `const std::string& s = make_long_string();` ——**生命周期延长**。语言保证：临时对象绑定到 const lvalue 引用时，临时对象的生命周期延长到引用变量的作用域结束（§6.7.7 [class.temporary]/6.6）。三次 `do_xxx(s)` 都安全。**零拷贝、零移动**——绑定就是别名。这是 Bjarne 在 C++98 就引入的"const reference extends lifetime"规则，至今仍是 C++ 最重要的内存安全特性之一。
- **B** `auto& s = make_long_string();` ——**编译失败**。`make_long_string()` 返回的是 prvalue（纯右值），不能绑定到非 const lvalue 引用。`auto&` 等价于 `T&`（非 const）—— prvalue 不能绑到它上面。这是 C++ 的硬规则：**非 const lvalue 引用不能绑到临时**。如果你想"灵活"——非 const、能修改——就必须自己拥有这个对象（D 的方案）。
- **C** `std::string&& s = make_long_string();` ——**也延长生命周期**！rvalue reference 绑到临时同样触发 lifetime extension（同条款）。语义上和 A 几乎相同，但有两个微妙不同：
  1. `s` 的类型是 `std::string&&`（rvalue ref），但 `s` 这个**名字本身是 lvalue**（命名的 reference 永远是 lvalue）。所以 `do_one(s)` 时 `s` 仍然像普通对象那样传——并不会被 move 走。
  2. 但作者**写出 `&&`** 是在向读者发出"我准备 move 这个对象"的信号——读者会以为接下来某处会 `std::move(s)`。三次 `do_xxx(s)` 平淡使用，**`&&` 是一个误导性的修饰符**。`const T&` 的语义"我只读" 更准确。
- **D** `std::string s = make_long_string();` ——**正确但浪费**。这是 copy/move 初始化——C++17 起保证 mandatory copy elision（prvalue 直接构造在 s 的位置，零拷贝），所以**性能上和 A、C 都一样**。区别在于**类型语义**：D 写出来 s 是一个**独立的、可变的 std::string 对象**，调用方能修改它。如果 `do_one/two/three` 不需要修改、且 you yourself 也不修改——按值接是过度承诺。
  
  但如果 `do_one(s)` 之后你想 `s += suffix` 修改，那 D 反而是对的选择。**所以 D 在"我想可变"的需求下不浪费**——只是题目暗示的"在多次操作里复用、不修改"语义匹配 A 更好。

C++17 的 mandatory copy elision 让 A vs D 的性能差异消失，区别全在**语义信号**：

| 写法 | 语义信号 |
|------|----------|
| `const T& s = ...` | "我只读，且我不拥有它" |
| `T&& s = ...` | "我准备 move 它"（但其实命名后又不能直接 move） |
| `T s = ...` | "我拥有它，能改它" |

**A 用 `const&` 表达"只读的别名"是最简洁的诚实**。

**核心识别点**：

- **生命周期延长**只对 `const T&` 和 `T&&` 绑定到 prvalue 时生效——对 `T&`（非 const 左值引用）不生效（编不过）
- 知道 prvalue（`f()` 的返回值）只能绑 `const T&` 或 `T&&`，**不能** 绑 `T&`
- 用 `T&&` 命名一个临时**没有 move 效果**——命名的 reference 是 lvalue
- C++17 的 mandatory copy elision 让 `T s = f();` 在 prvalue 初始化时零拷贝——按值接不再"昂贵"
- 选 `const T&`、`T s`、`T&&` 是**语义选择**——表达"借用 / 拥有 / 即将 move"

特别注意：lifetime extension **不**会跨越函数边界。如果你写 `const T& f() { return some_temp; }`，返回的 const reference 在调用方手里**仍然是悬空**——extension 只发生在直接初始化时，不发生在 return 时。这是经常被忽略的细节。

**来源：** 手写题。生命周期延长规则见 ISO/IEC 14882 §6.7.7 [class.temporary]/6；mandatory copy elision (C++17) 见 §12.8/31；Herb Sutter "GotW #88: A Candidate For the 'Most Important const'"。