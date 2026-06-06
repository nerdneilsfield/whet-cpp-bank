---
qid: cpp-taste-algo-014
type: single
kp: [cpp-algorithms, cpp-iterators, cpp-stl-basics]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: C
tags: [code-taste, best-practice]
---

要生成一个从 1 到 N 的整数序列放入 vector。下面四个写法功能相同，哪个最有 C++ 味？

```cpp
// A
const int N = 10;
std::vector<int> v(N);
for (int i = 0; i < N; ++i) {
    v[i] = i + 1;
}

// B
const int N = 10;
std::vector<int> v(N);
int x = 1;
std::generate(v.begin(), v.end(), [&x]() { return x++; });

// C
const int N = 10;
std::vector<int> v(N);
std::iota(v.begin(), v.end(), 1);

// D
const int N = 10;
std::vector<int> v;
for (int i = 1; i <= N; ++i) {
    v.push_back(i);
}
```

A. A — 下标赋值，最基础

B. B — generate + mutable lambda

C. C — iota，标准递增序列发生器

D. D — push_back 循环

---

**解析：**

选 C。`std::iota` 的名字来自 APL 语言的 `⍳`（希腊字母 iota），是 Fortran/APL 概念在 C++ 标准库里的映射。它是**专门做递增序列**的 algorithm。

逐一品味为什么其他版本不好：

- **A**：下标循环 + 赋值，没有利用任何 algorithm。读者看完循环才明白"哦，这是生成 1..N"。

- **B**：`generate` 配合 mutable lambda 能工作，但 `generate` 的语义是"无状态生成器填充范围"——任何序列都可以用 `generate` 生成，不一定是递增的。读者看到 `generate` 会想"它生成什么东西？"而看到 `iota` 会直接知道"它是递增序列"。

- **D**：循环内 `push_back` 每次可能触发 reallocation，性能最差。即使 `reserve` 了，也没有 algorithm 表达"填充递增整数"的意图直接。

`iota` 是 C++98 就加入的 algorithm。它的签名是 `void iota(ForwardIt first, ForwardIt last, T value)`，效果是 `*first++ = value++` 直到范围填满。简单的名字，明确的语义。

核心识别点：
- 递增序列 → `iota`
- 任意序列生成 → `generate`
- 转换现有范围 → `transform`
- `iota` 不要求随机访问迭代器（forward iterator 即可），但预分配大小是必须的