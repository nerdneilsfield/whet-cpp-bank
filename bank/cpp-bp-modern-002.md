---
qid: cpp-bp-modern-002
type: single
kp: [cpp-cpp14-17]
difficulty: medium
answer_key: B
---

以下代码哪个使用 structured bindings（C++17）最现代化、最高效？

```cpp
std::map<std::string, int> scores = { {"alice", 90}, {"bob", 85} };

// A
for (auto pair : scores) {
    std::cout << pair.first << ": " << pair.second << "\n";
}

// B
for (const auto& [name, score] : scores) {
    std::cout << name << ": " << score << "\n";
}

// C
for (auto& [name, score] : scores) {
    std::cout << name << ": " << score << "\n";
}

// D
for (auto [name, score] : scores) {
    std::cout << name << ": " << score << "\n";
}
```

A. A
B. B
C. C
D. D

---

**解析：**

逐个评估：

- **A**：`auto pair` 拷贝整个 `std::pair<const std::string, int>`，每次循环都拷贝 string——**最差**
- **B**：`const auto& [name, score]`，引用绑定，零拷贝；只读。**最优**
- **C**：`auto& [name, score]`，引用绑定，但允许修改。注意 map 的 key 是 `const std::string`，仍可写 value；但语义上要不要写应当显式
- **D**：`auto [name, score]`，**每次循环拷贝整个 pair**（虽然写法看似简洁）——和 A 一样有拷贝开销

structured bindings 不会"自动用引用"。`auto [a, b] = pair;` 等价于 `auto __tmp = pair; auto& a = std::get<0>(__tmp); ...`，**__tmp 是值拷贝**。

工程准则：
- 只读 → `const auto& [...]`
- 写入 → `auto& [...]`
- 移动语义 → `auto&& [...]`（universal reference）

补充：structured bindings 适用于：
- `std::pair` / `std::tuple` / `std::array`
- 任何带 `get<I>(obj)` 函数 + `tuple_size`/`tuple_element` 特化的类型
- 简单聚合体（struct 的 public 字段）

例：
```cpp
struct Point { int x, y; };
Point p{1, 2};
auto& [x, y] = p;
x = 10;  // 修改 p.x

// 函数返回多值
auto [iter, inserted] = mp.insert({k, v});
auto [min, max] = std::minmax({1, 2, 3, 4});
```

C++17 之前用 `std::tie`，要先声明变量。structured bindings 是更现代、更可读的写法。

正确答案 B。