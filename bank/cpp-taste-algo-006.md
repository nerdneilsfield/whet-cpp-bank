---
qid: cpp-taste-algo-006
type: single
kp: [cpp-algorithms, cpp-stl-basics]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: C
tags: [code-taste, best-practice]
---

要检查 vector<int> 中**所有**元素是否都是正数。下面四个写法功能相同，哪个最有 C++ 味？

```cpp
// A
bool all_positive(const std::vector<int>& v) {
    for (auto x : v) {
        if (x <= 0) return false;
    }
    return true;
}

// B
bool all_positive(const std::vector<int>& v) {
    return std::find_if(v.begin(), v.end(),
                        [](int x) { return x <= 0; }) == v.end();
}

// C
bool all_positive(const std::vector<int>& v) {
    return std::all_of(v.begin(), v.end(),
                       [](int x) { return x > 0; });
}

// D
bool all_positive(const std::vector<int>& v) {
    return std::count_if(v.begin(), v.end(),
                         [](int x) { return x <= 0; }) == 0;
}
```

A. A — range-for + early return，简单直接

B. B — find_if 直到 end，比 A 更规范

C. C — all_of 一句话，意图最明确

D. D — count_if == 0，一行搞定

---

**解析：**

选 C。`all_of` 的名字就是你想问的问题："**所有**元素都满足吗？"

逐一品味为什么其他版本不好：

- **A**：range-for 加 early return，逻辑上是对的。但它把"检查全正"翻译成了"遍历，如果找到不满足的就返回 false"。读者必须读完循环体才能反应过来这是在做什么。一旦循环体变长（哪怕只是多几行调试日志），意图就淹没在控制流里了。

- **B**：`find_if` 直到 `end()` 等价于"没找到违规的"，语义是"否定之否定"：`v 中没找到 <=0 的元素`。大脑要绕一个弯：`end()` 表示"没找到"→ "没找到违规的"→ "所以全是正的"。

- **D**：和前几题一样的问题——`count_if` 不能短路，必须遍历全部。如果 vector 很大、第一个元素就是 <=0 的，D 仍然要扫完整个容器。复杂度承诺完全不同：`all_of` 在遇到第一个不满足条件时就返回 `false`。

核心识别点：
- 问"全部满足" → `all_of`
- 问"存在一个" → `any_of`
- 问"没有一个" → `none_of`
- 这些 algorithm 都有短路语义，`count_if` 没有
- 如果已经知道所有元素都满足，`all_of` 是最差情况 O(n)；而 `count_if` 永远是 O(n)——所以 `all_of` 永远不会更差，有时更好

## Explanation

正确答案是 C。`all_of` 的名字就是你想问的问题："所有元素都满足吗？
复杂度承诺完全不同：`all_of` 在遇到第一个不满足条件时就返回 `false`。
D：和前几题一样的问题——`count_if` 不能短路，必须遍历全部。
