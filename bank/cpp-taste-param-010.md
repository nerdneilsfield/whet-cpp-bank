---
qid: cpp-taste-param-010
type: single
kp: [cpp-functions, cpp-cpp14-17]
primary_kp: cpp-functions
difficulty: hard
answer_key: D
---

在 map 里按 key 查找值，函数需要表达"找到了 / 没找到"。从**参数传递品味**的角度，哪段写得最好？

```cpp
// A
bool lookup(const std::map<std::string, int>& m, const std::string& key, int& out) {
    auto it = m.find(key);
    if (it == m.end()) return false;
    out = it->second;
    return true;
}
```

```cpp
// B
int* lookup(const std::map<std::string, int>& m, const std::string& key) {
    auto it = m.find(key);
    return it == m.end() ? nullptr : &it->second;
}
```

```cpp
// C
int lookup(const std::map<std::string, int>& m, const std::string& key, bool& found) {
    auto it = m.find(key);
    found = it != m.end();
    return it == m.end() ? 0 : it->second;
}
```

```cpp
// D
std::optional<int> lookup(const std::map<std::string, int>& m, const std::string& key) {
    auto it = m.find(key);
    if (it == m.end()) return std::nullopt;
    return it->second;
}
```

A. A 段：`bool + T& out` 是 C 语言过来的传统写法，意图一目了然。
B. B 段：返回 `int*`，`nullptr` 表示"不存在"，指针有效期与容器一致，自然。
C. C 段：out bool + 返回值 c 分"是否存在"和"值是多少"，明确分离。
D. D 段：`std::optional<int>` 返回值既表示成功/失败又携带值，类型驱动。

## 解析

正确答案是 **D**。

- **A 段（差）**：调用点 `int v; if (lookup(m, "x", v)) { ... }` 里 `v` 必须声明但未初始化——如果 `lookup` 在 find 时提前返回 false，那就有一条**读了未初始化变量**的值路径（实际返回 false、out 没写，但调用方不小心用了 `v` 就出事）。out 引用还有 const-correctness 问题：不能传 `const int` 进去。
- **B 段（差）**：不可行——`map::value_type` 的 `second` 是 const 的（`const int`），返回 `int*` 需要 `const_cast` 掉 const；即使多写 `const int*`，指针家在 map 的节点上，下一个插入/删除操作就是悬空。API 的被用隐式前提（"别改 map"）没有类型系统约束。
- **C 段（差）**：调用点必须声明一个 `bool found` 的占位变量，纯噪点；返回值 `0` 既是合法值又是"未找到"的冗余哨兵——如果 map 里存的是 `0`，返回值无法区分"找到 0"和"没找到"。
- **D 段（好）**：`std::optional<int>` 在类型系统层面编码"可能有值"。调用点 `if (auto v = lookup(m, "x")) { use(*v); }` 既清楚又有类型保证；如果 map 里存了 `0`，`optional<int>` 正确携带 `0`，不做歧义判断。

**核心识别点：**
- 可选值返回值用 `std::optional<T>`（C++17），而非 bool + out 参数或哨兵值。
- out 引用存在"未初始化读"风险和 const-correctness 问题。
- 返回指针表示"可选"在 C++ 里只有 `nullptr == absent` 一个状态，但指向 map 内部有生命周期依赖。
- 哨兵值（`-1`、`nullptr`、`0`）无法区分"真的到这个值"和"不存在"。

**来源：** C++ Core Guidelines F.23（"Prefer optional<T> over pair<bool, T>"）；Effective Modern C++ Item 35；cppreference `std::optional`。