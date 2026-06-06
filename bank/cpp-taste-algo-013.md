---
qid: cpp-taste-algo-013
type: single
kp: [cpp-algorithms, cpp-iterators, cpp-stl-basics]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: B
tags: [code-taste, best-practice]
---

要把 vector<int> 中所有负数替换为 0，结果放到新容器，**不修改原容器**。下面四个写法功能相同，哪个最有 C++ 味？

```cpp
// A
std::vector<int> src{-3, 5, -1, 0, 2, -7};
std::vector<int> dst;
std::transform(src.begin(), src.end(),
               std::back_inserter(dst),
               [](int x) { return x < 0 ? 0 : x; });

// B
std::vector<int> src{-3, 5, -1, 0, 2, -7};
std::vector<int> dst;
std::replace_copy_if(src.begin(), src.end(),
                     std::back_inserter(dst),
                     [](int x) { return x < 0; },
                     0);

// C
std::vector<int> src{-3, 5, -1, 0, 2, -7};
std::vector<int> dst;
for (auto x : src) {
    dst.push_back(x < 0 ? 0 : x);
}

// D
std::vector<int> src{-3, 5, -1, 0, 2, -7};
std::vector<int> dst(src);
std::replace_if(dst.begin(), dst.end(),
                [](int x) { return x < 0; },
                0);
```

A. A — transform + lambda，用三目运算符替换

B. B — replace_copy_if，名字就在说"复制时替换"

C. C — range-for + push_back，可控

D. D — 复制到 dst 再 in-place replace_if

---

**解析：**

选 B。`replace_copy_if` 这个名字完美地描述了正在做的事："复制范围到新位置，同时根据条件替换元素"。

逐一品味为什么其他版本不好：

- **A**：`transform` + 三目运算符虽然能工作，但语义是"对每个元素做变换"——替换(0)只是变换的一个特例。当你用 `transform` 来做替换时，读者会想"为什么要用 transform？是不是还有其他变换？"——代码意图不够精确。用专门的 algorithm 总是好于通用的。

- **C**：手写循环 + push_back。逻辑上没错，但要把"复制时替换"这个动作拆解成"遍历、条件判断、三元运算、push_back"四个步骤，读者需要在脑子里重新编译一次。而且没有 `reserve`，会有多次 reallocation。

- **D**：两步法——先复制整个容器，再 in-place replace_if。需要额外的分配和一次完整拷贝。对于大容器，这是无谓的浪费。`replace_copy_if` 可以一次完成。

`replace_copy_if` 在 C++98 就已存在。它有四个参数：输入范围、输出目的地、谓词、新值。名字明确告诉你它在做什么——"replace" + "copy" + "if" = "复制时按条件替换"。

核心识别点：
- "复制 + 替换" → `replace_copy`（替换值）或 `replace_copy_if`（替换条件）
- "原地替换" → `replace` / `replace_if`
- "通用的变换" → `transform`
- 尽量用名字精确的 algorithm，不要用通用的算法做特化的事