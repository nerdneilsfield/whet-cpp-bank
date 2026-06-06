---
qid: cpp-taste-algo-015
type: single
kp: [cpp-algorithms, cpp-stl-basics]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: C
tags: [code-taste, best-practice]
---

对一个 vector<int> 求所有元素的和。下面四个写法功能相同，哪个最有 C++ 味？

```cpp
// A
std::vector<int> v{1, 2, 3, 4, 5};
int sum = 0;
for (auto x : v) sum += x;

// B
std::vector<int> v{1, 2, 3, 4, 5};
int sum = std::reduce(std::execution::par, v.begin(), v.end(), 0);

// C
std::vector<int> v{1, 2, 3, 4, 5};
int sum = std::accumulate(v.begin(), v.end(), 0);

// D
std::vector<int> v{1, 2, 3, 4, 5};
std::vector<int> partials(v.size());
std::partial_sum(v.begin(), v.end(), partials.begin());
int sum = partials.back();
```

A. A — 手写循环，轻量直接

B. B — 并行 reduce，追求极致性能

C. C — accumulate，标准求和

D. D — partial_sum 收集部分和再取最后

---

**解析：**

选 C。`std::accumulate` 是标准库中最直接的求和 algorithm，名字本身就是"累加"——"Add up all elements"。

逐一品味为什么其他版本不好：

- **A**：手写循环，把"求和"这个操作翻译成了"遍历 + 累加"。读者要理解循环在做什么。**意图没有被命名**。对于求和这样简单的事，手写循环可以接受，但用 `accumulate` 更直接——名字就是操作。

- **B**：`std::reduce` 是 C++17 引入的并行友好版本。问题在于：`reduce` 不保证操作顺序，因此要求**操作是可交换且可结合**的。`int` 加法是可交换的，没问题。但这里的 `std::execution::par` 引入了并行调度的开销，对于只有 5 个元素的 vector，**并行的调度开销远超求和本身的计算开销**。盲目上并行是不好的品味。

- **D**：用 `partial_sum` 求所有元素的和——这是**杀鸡用牛刀还选错了刀**。`partial_sum` 的语义是"每个位置放从起始到该位置的部分和"，它的输出序列里有 n 个值，你只取最后一个。这用了 O(n) 额外空间，O(n) 额外时间，就为了最后一个值。

`accumulate` 的复杂度是精确 O(n)，没有额外分配，没有并行开销，**在所有场景下都是"求和"的正确默认选择**。

核心识别点：
- "所有元素的和" → `accumulate`
- "可交换操作的归约" → `reduce`（仅在不关心顺序或需要并行时）
- "并行"有启动成本——数据量不够大时不要用
- `partial_sum` 的用途是"中间结果"或"微分/积分"操作，不是求最终和