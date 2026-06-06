---
qid: cpp-taste-init-010
type: single
kp: [cpp-cpp11, cpp-stl-basics]
primary_kp: cpp-cpp11
difficulty: hard
answer_key: B
tags: [code-taste, best-practice, initializer-list, iil-trap]
---
要创建一个 `std::string` 的 `vector`，存放某个 token 序列的前 3 个结果。`tokens` 是一个 `std::vector<std::string>` 且有至少 3 个元素。四个写法功能完全相同，哪个最好？

```cpp
// A
auto v = std::vector<std::string>{tokens[0], tokens[1], tokens[2]};

// B
auto v = std::vector<std::string>(tokens.data(), tokens.data() + 3);

// C
std::vector<std::string> v{tokens[0], tokens[1], tokens[2]};

// D
std::vector<std::string> v(tokens.begin(), tokens.begin() + 3);
```

A. A — `auto` + `{}`，最简洁
B. B — 用指针区间构造，意图清楚、参数不需要迭代器头文件
C. C — `{}` + 显式类型，比 A 更明确
D. D — 用迭代器区间构造，标准的 STL 惯用法

---

**解析：**

选 D。这道题的陷阱不在 `vector{3,5}` 那个众所周知的坑——它考的是 **"3 个同类型参数的 `{}` 看起来不会出 initializer_list 问题？但你忘了 vector<string> 的三个元素可能是不同类型时的问题，以及更微妙的：iterator pair constructor 和 initializer_list 在 `{}` 下的冲突"**。

A、C 都是 `{}`，D 是 `()`，B 是 `()` 但是指针。

逐一品味：

- **A / C** `std::vector<std::string>{tokens[0], tokens[1], tokens[2]}` ：这里三个元素全是 `std::string`，所以 `initializer_list<std::string>` 构造一切正常，看起来是"安全的"。**但问题是 `{}` 有不对的地方吗？** 它的不对在于——如果你不小心写成了 `std::vector<long long>{a, b, c}` 其中 a/b/c 是 `int`——那么 initializer_list 不会遇到 narrowing，**它隐式转换**，没事。这里似乎平安无事。但是 A 和 C 的问题是**可读性**：`vector{v[0], v[1], v[2]}` 需要读者理解"你在初始化列表里放三个元素"vs"你其实在拷贝三个已有元素过去"。更根本的是，`conditions` 一旦变成不是连续三个位置的（比如跳过某个），就得重写这本。**`{}` 在这里没错，但表达能力不够普遍**。

- **B** `std::vector<std::string>(tokens.data(), tokens.data() + 3);` ：用 `data() + count` 构造 vector——意图是"从前 3 个元素拷贝"。但这里隐藏了一个**类型假设**：`tokens.data()` 返回 `std::string*`，`+ 3` 是老 `T*` 指针算术，完全合法。但万一 `tokens` 不是 `vector` 而是 `std::list`（`data()` 不存在）或 `deque`，B 就编不过了。它把代码耦合到了"连续存储"这个实现细节——虽然 `std::vector` 保证连续。

- **D** `std::vector<std::string>(tokens.begin(), tokens.begin() + 3);` ：这是 **STL 的开区间迭代器构造**（InputIterator pair），是容器构造中最通用、最符合 STL 哲学的写法。它告诉读者"我想拿 tokens 里从 begin 到 begin+3 这个范围构造一个新 vector"，无论 tokens 什么容器（vector/deque/array/C array），只要有 ForwardIterator，通吃。不依赖 `data()` 的存在，不担心 `{}` 的歧义。**STL 的"通用性"红利在此**。

这里最微妙的是：如果 tokens 的 `begin()` 和 `begin()+3` 的类型不适合 initializer_list（比如它们都是 `int*`），那么 D 在 `{}` 下会怎么样？

```cpp
// 一个人可能误写成：
std::vector<int> v{tokens.data(), tokens.data() + 3};
```

**这就是题 10 的隐藏陷阱**：当 `tokens` 的元素类型也是 `int` 时，`tokens.data()` 和 `tokens.data()+3` 返回的都是 `int*`，而 `int*` 可以隐式转换成 `int`（饿，不对——指针不能隐式转 int）。等等，这里指向的容器已经是 `std::string`，没事。

更真实的陷阱是：

```cpp
// 如果 tokens 是个 C 风格数组 int tokens[] = {1,2,3,4,5};
std::vector<int> v{tokens, tokens + 3};  // 不是迭代器构造！
// 而是 initializer_list<???> 尝试编译...
```

实际上对于 `vector<int> v{tokens, tokens + 3}` 当 tokens 是 `int*` 时，`{int*, int*}` 不是 `initializer_list<int>` 可以接受的类型，所以回退到 iterator pair 构造，反而正确！但对 `string` 这种事不存在。

选 D 的理由最终落在：**用 `()` 区间构造是表达"从一个范围复制元素到新容器"的最忠实的语法**。`{}` 是表达"列出内容"的语法。让 `{}` 和 `()` 在 container 构造上各守其语意——`()` 范围、`{}` 内容——是最有品味的做法。

**核心识别点**：

- `{}` 在 `vector` 上会触发 initializer_list 构造优先级——即使所有元素同类型，语义也是"一一列举"
- `()` 在 `vector` 上走的是非-initializer_list 构造——count + value、iterator pair、copy/move
- 看到 `v.data(), v.data() + n` 时考虑是否该用 `v.begin(), v.begin() + n`（更通用）
- 用 `()` 表达"从别处拷贝来"，用 `{}` 表达"这里列出存什么"——风格一致

题 1（001）和题 10（010）是从两个方向打 `{}` vs `()` 的问题：001 是 `vector<int> v{n}`（你以为长度，实际 single element），010 是 `vector<string> v{a, b, c}`（虽然没错，但和 iterator 构造语义不同），根本都在 initializer_list 构造函数无条件压倒一切。

**来源：** 手写题。initializer_list 构造 vs 其他构造的优先级见 ISO/IEC 14882 §16.3.5 [over.match.best]/2.8；Scott Meyers *Effective Modern C++* Item 7 "Distinguish between () and {} when creating objects"。

## Explanation

正确答案是 D 的理由最终落在：用 `()` 区间构造是表达"从一个范围复制元素到新容器"的最忠实的语法。
逐一品味： A / C `std::vector<std::string>{tokens[0], tokens[1], tokens[2]}` ：这里三个元素全是 `std::string`，所以 `initializer_list<std::string>` 构造一切正常，看起来是"安全的"。
这道题的陷阱不在 `vector{3,5}` 那个众所周知的坑——它考的是 "3 个同类型参数的 `{}` 看起来不会出 initializer_list 问题？
