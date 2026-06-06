---
qid: cpp-taste-algo-007
type: single
kp: [cpp-algorithms, cpp-stl-basics]
primary_kp: cpp-algorithms
difficulty: hard
answer_key: D
tags: [code-taste, best-practice]
---

要求 vector<int> 中所有**正数**的平方和。下面四个写法功能相同，哪个最有 C++ 味？

```cpp
// A
std::vector<int> v;
// ... fill v ...
int sum = 0;
for (auto x : v) {
    if (x > 0) sum += x * x;
}

// B
std::vector<int> v;
// ... fill v ...
std::vector<int> squares;
for (auto x : v) {
    if (x > 0) squares.push_back(x * x);
}
int sum = std::accumulate(squares.begin(), squares.end(), 0);

// C
std::vector<int> v;
// ... fill v ...
int sum = 0;
std::for_each(v.begin(), v.end(),
              [&sum](int x) { if (x > 0) sum += x * x; });

// D
std::vector<int> v;
// ... fill v ...
auto r = v | std::views::filter([](int x) { return x > 0; })
          | std::views::transform([](int x) { return x * x; });
int sum = std::ranges::fold_left(r, 0, std::plus{});
```

A. A — 单次循环，高效直接

B. B — 先用 vector 收集再 accumulate，步骤分明

C. C — for_each + 外部累加，比 for 循环更函数式

D. D — ranges view 链式管道，表达力最强

---

**解析：**

选 D。C++20 的 ranges 库让"过滤 → 变换 → 归约"这种经典三板斧变成了一行管道。

逐一品味为什么其他版本不好：

- **A**：单循环虽然高效，但混合了**遍历、条件判断、计算**三个关注点。未来如果要改成"只求偶数位置的正数平方和"就必须侵入循环体改逻辑。代码越混合，可复用性越差。

- **B**：先构造中间容器 `squares`，多了一次 O(n) 分配和拷贝。这个中间数组可能很大（如果原容器有 1 亿个正数），而且它的唯一使命是作为一个过渡传给 `accumulate`。浪费。

- **C**：`for_each` + 捕获引用的 lambda 是对"有副作用的操作"的妥协。`for_each` 本来的语义是"对每个元素做某事，不考虑返回值"，但这里明显是一个归约操作。用 `for_each` 做归约是把 algorithm 用在了不适合的地方。`accumulate` 或 `fold_left` 的名字才表达"归约"。

D 的做法：`filter` 留下正数，`transform` 映射为平方，`fold_left` 归约为和。每一步**零中间分配**（视图是惰性的），名字就是意图。这是 C++23 `fold_left` 加上 range 管道的理想组合。

核心识别点：
- 旧标准（C++17 以下）：只能用 `std::accumulate` + 手写条件（但 accumulate 本身不支持过滤），或写循环。
- 涉及过滤 + 变换 + 归约 → 首选 ranges 管道。
- 不要为一次归约构造中间容器。
- 不要用 `for_each` 做归约。