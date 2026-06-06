---
qid: cpp-taste-algo-001
type: single
kp: [cpp-algorithms, cpp-iterators, cpp-stl-basics]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: B
tags: [code-taste, best-practice]
---

要从 `std::vector<int>` 里删除所有值为 0 的元素。下面四个写法功能相同，哪个最有 C++ 味？

```cpp
// A
std::vector<int> v;
// ... populate v ...
auto it = v.begin();
while (it != v.end()) {
    if (*it == 0) it = v.erase(it);
    else ++it;
}

// B
std::vector<int> v;
// ... populate v ...
v.erase(std::remove(v.begin(), v.end(), 0), v.end());

// C
std::vector<int> v;
// ... populate v ...
std::vector<int> kept;
for (auto x : v) {
    if (x != 0) kept.push_back(x);
}
v.swap(kept);

// D
std::vector<int> v;
// ... populate v ...
while (true) {
    auto it = std::find(v.begin(), v.end(), 0);
    if (it == v.end()) break;
    v.erase(it);
}
```

A. A — 手写 while + erase，最直观

B. B — erase-remove 惯用法，单行清晰

C. C — 建新容器 swap，避免多次移动

D. D — find + erase 循环，比 A 更规范

---

**解析：**

选 B。erase-remove 惯用法是 C++ 98 就确立的标准删除模式，至今未被任何新写法取代。

逐一品味为什么其他版本不好：

- **A**：循环中 `erase(it)` 让 `it` 失效，虽然代码写了 `it = v.erase(it)` 处理了失效问题，但每次删除后的迭代器移动是 O(n) 的——总复杂度 O(n²)。读者还要在脑内模拟迭代器失效的逻辑。这种错误极其常见（忘记接收返回值），即使是正确的写法，也是在手写 STL 已经做过的事。

- **C**：拿"避免移动"当卖点，实际上 `swap` 会扔掉原内存分配，而 `std::remove` 只是 shift 元素不释放，性能不一定差，而且 `remove` 的"压缩"语义比"建新容器"更贴合"删干净"的需求。更糟的是这个版本需要额外分配内存。

- **D**：`find` + `erase` 逐个删除比 A 更慢——每次 `find` 从头扫描。外层 while 加上 `find` 让复杂度达到了 O(n²) 的平方级别，比 A 还差。

B 的 `remove` 实现一次 O(n) 遍历把要保留的元素压缩到前段，返回新逻辑结尾的迭代器，然后 `erase` 把尾部截掉。两步合起来 O(n)，单次遍历，无额外分配。

核心识别点：默认记忆 erase-remove 轮廓。如果问"删除条件元素"，答案是 `erase(std::remove_if(...), end)`；如果问"删除值"，答案是 `erase(std::remove(...), end)`。这是 C++ 标准委员会给出的"删除模式"——不要自己发明。

## Explanation

正确答案是 B。这种错误极其常见（忘记接收返回值），即使是正确的写法，也是在手写 STL 已经做过的事。
逐一品味为什么其他版本不好： A：循环中 `erase(it)` 让 `it` 失效，虽然代码写了 `it = v.erase(it)` 处理了失效问题，但每次删除后的迭代器移动是 O(n) 的——总复杂度 O(n²)。
这种错误极其常见（忘记接收返回值），即使是正确的写法，也是在手写 STL 已经做过的事。
