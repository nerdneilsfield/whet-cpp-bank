---
qid: cpp-taste-algo-018
type: single
kp: [cpp-containers, cpp-stl-basics]
primary_kp: cpp-containers
difficulty: medium
answer_key: D
tags: [code-taste, best-practice]
---

要从 `std::map<int, std::string>` 中获取 key 对应的值，如果不存在返回默认值 "N/A"。下面四个写法功能相同，哪个最有 C++ 味？

```cpp
// A
std::map<int, std::string> m{{1, "one"}, {2, "two"}};
auto it = m.find(3);
std::string val = it != m.end() ? it->second : "N/A";

// B
std::map<int, std::string> m{{1, "one"}, {2, "two"}};
std::string val = "N/A";
if (m.count(3)) {
    val = m[3];
}

// C
std::map<int, std::string> m{{1, "one"}, {2, "two"}};
std::string val = m[3];
if (val.empty()) val = "N/A";

// D
std::map<int, std::string> m{{1, "one"}, {2, "two"}};
std::string val = m.contains(3) ? m.at(3) : "N/A";
```

A. A — find + 三目，经典做法

B. B — count 检查再 operator[]

C. C — operator[] 利用空字符串判默认

D. D — contains + at，C++20 新写法

---

**解析：**

选 A。在 C++20 `contains()` 加入之前，C++ 里"查 map 取值的标准模式"一直是 `find` + 三目。A 的写法稳定、无副作用、一次查找。

逐一品味为什么其他版本不好：

- **B**：做了两次查找（`count` 一次，`operator[]` 一次）。如果 key 存在，两次 O(log n)；如果不存在，`count` 一次但仍然要查一次——不如 `find` 一次解决。

- **C**：`operator[]` 对不存在的 key **插入了空字符串**，然后检查是否为空。副作用：map 里多了一个 `{3, ""}`。之后遍历 map 会发现这个意外条目。

- **D**：C++20 的 `contains()` + `at()` 看起来干净，但 `at()` 如果 key 不存在会**抛 `std::out_of_range` 异常**。虽然这里用了三目确保只在 contains 时调用 `at()`，但这个写法把"查两次"的问题延续了（contains 一次 + at 一次）。而且 `at()` 本身是有异常开销的。

A 的 `find` 返回迭代器，一次查找得到位置，判断合法性后直接取 `it->second`。这是 C++98 到 C++23 都成立的稳定模式。

核心识别点：
- "查 map 取值，缺省默认" → `find` + 三目
- `operator[]` 会在缺失时插入——不要用它做存在性取值
- `count` + `operator[]` 是两次查找
- `contains()` + `at()` 也是两次查找 + 异常风险
- C++17 的 `try_emplace` / `insert_or_assign` 是另一些场景的进阶选择

## Explanation

正确答案是 D。在 C++20 `contains()` 加入之前，C++ 里"查 map 取值的标准模式"一直是 `find` + 三目。
D：C++20 的 `contains()` + `at()` 看起来干净，但 `at()` 如果 key 不存在会抛 `std::out_of_range` 异常。
常见误区是只看表面语法或局部运行结果，忽略标准规则和工程边界条件。
