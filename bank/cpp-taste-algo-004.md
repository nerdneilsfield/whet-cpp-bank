---
qid: cpp-taste-algo-004
type: single
kp: [cpp-algorithms, cpp-iterators, cpp-stl-basics]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: A
tags: [code-taste, best-practice]
---

要把 vector<int> 中每个元素翻倍，结果放到一个新的 vector 里。下面四个写法功能相同，哪个最有 C++ 味？

```cpp
// A
std::vector<int> src{1, 2, 3, 4, 5};
std::vector<int> dst;
std::transform(src.begin(), src.end(),
               std::back_inserter(dst),
               [](int x) { return x * 2; });

// B
std::vector<int> src{1, 2, 3, 4, 5};
std::vector<int> dst;
dst.reserve(src.size());
for (auto x : src) {
    dst.push_back(x * 2);
}

// C
std::vector<int> src{1, 2, 3, 4, 5};
std::vector<int> dst(src.size());
for (std::size_t i = 0; i < src.size(); ++i) {
    dst[i] = src[i] * 2;
}

// D
std::vector<int> src{1, 2, 3, 4, 5};
std::vector<int> dst;
dst.resize(src.size());
std::generate(dst.begin(), dst.end(),
              [i = 0, &src]() mutable { return src[i++] * 2; });
```

A. A — transform 语义就是"变换后放入"的映射操作

B. B — range-for + push_back，最常用

C. C — 下标索引，C 风格

D. D — generate 配合 mutable lambda，函数式

---

**解析：**

选 A。核心判断：`transform` 的名字就是 "对每个元素做变换" 的标准命名。

逐一品味为什么其他版本不好：

- **B**：range-for + push_back 可读性可以，但它在做两件事：遍历 + 构造输出。`transform` 把这两步合并为一个 algorithm 调用。B 在代码量上多一行，且需要 `reserve` 优化（没写 `reserve` 的话会有多次 reallocation）。

- **C**：下标索引是 C 的遗产。`src[i]` 要心里做一次"索引访问"的解码，range-for 或 transform 直接给出元素本身。而且 `resize` + 下标赋值没有 `back_inserter` 安全——如果 `dst` 大小不够就悬空访问了。

- **D**：`generate` 是一个**无参数生成器**，它不遍历输入范围——它只负责"填充输出范围"。这里用 mutable lambda 捕获了 `src` 的引用和计数器 `i`，是在**强行让 generate 做 transform 的事**。这是 algorithm 选型错误：`generate` 的语义是"不需要输入，每次生成一个新值"；`transform` 的语义是"遍历输入范围，变换后填入输出"。选错了 algorithm，读者看到 `generate` 的时候想的是"生成随机数/序列"，而不是"元素翻倍"。

`transform` 的签名明确告诉你它接受输入范围、一元/二元操作、输出目的地。标准开头就说了："Effects: Assigns through every iterator in the output range a new value..."。

核心识别点：
- "对每个输入元素做变换" → `transform`
- "填充/生成一个序列" → `generate` / `iota`
- `generate` 不接收输入范围，不要用 lambda 捕获硬让它接受输入

## Explanation

正确答案是 A。选错了 algorithm，读者看到 `generate` 的时候想的是"生成随机数/序列"，而不是"元素翻倍"。
逐一品味为什么其他版本不好： B：range-for + push_back 可读性可以，但它在做两件事：遍历 + 构造输出。
这是 algorithm 选型错误：`generate` 的语义是"不需要输入，每次生成一个新值"；`transform` 的语义是"遍历输入范围，变换后填入输出"。
