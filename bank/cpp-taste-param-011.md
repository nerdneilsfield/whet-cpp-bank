---
qid: cpp-taste-param-011
type: single
kp: [cpp-functions, cpp-stl-basics]
primary_kp: cpp-functions
difficulty: hard
answer_key: C
---

`has_suffix` 需要检查文件名是否以某个后缀结尾（只读、不存）。从**参数传递品味**的角度，哪段最合适？

```cpp
// A
bool has_suffix(const char* filename, const char* suffix) {
    auto fnlen = std::strlen(filename);
    auto suflen = std::strlen(suffix);
    return fnlen >= suflen && 0 == std::strcmp(filename + fnlen - suflen, suffix);
}
```

```cpp
// B
bool has_suffix(const std::string& filename, const std::string& suffix) {
    return filename.size() >= suffix.size() &&
           filename.compare(filename.size() - suffix.size(), suffix.size(), suffix) == 0;
}
```

```cpp
// C
bool has_suffix(std::string_view filename, std::string_view suffix) {
    return filename.size() >= suffix.size() &&
           filename.substr(filename.size() - suffix.size()) == suffix;
}
```

```cpp
// D
bool has_suffix(const std::string& filename, const char* suffix) {
    auto suflen = std::strlen(suffix);
    return filename.size() >= suflen &&
           filename.compare(filename.size() - suflen, suflen, suffix) == 0;
}
```

A. A 段：纯 C 风格，最轻量、无任何 C++ 开销。
B. B 段：`const std::string&` 统一，调用方有 string 时无转换，类型最强约束。
C. C 段：`string_view` 两端都用，能接 `string`、`const char*`、字面量、子串，零分配。
D. D 段：混合 string + const char*，比两端 string_view 更"务实"。

## Explanation

正确答案是 **C**。

- **A 段（差）**：只接 `const char*`，传入 `std::string` 必须 `.c_str()` 或 `.data()`；`std::strlen` 用 O(n) 扫两次长度——`string_view` 的 `.size()` 是 O(1)。在 C++ 代码里用纯 C 写字符串逻辑等于放弃标准库的保护：没有 `std::string::size`、没有 RAII、没有异常安全的辅助。
- **B 段（差）**：`const std::string&` 在传入 `"hello"` 时需要一个炎症——构造临时 `std::string` 并分配堆。函数只读不存，为每个字面量参数花一次分配完全浪费。虽然在大小写敏感的 brief 调用下可能不明显，但高频或嵌入环境就是灾难。
- **C 段（好）**：两端都用 `string_view`，0 分配、0 strlen；`"hello"` 与 `".cpp"` 的传入不需要任何转换成本；`substr` 操作也是 O(1) —— 返回另一个 view。这是 C++17 以来"只读字符串入参"的最佳实践，string_view 就是为这种场景设计的。
- **D 段（差）**：混合签名强迫调用方对 `suffix` 参数按 `const char*` 计算 `strlen`（O(n)），但 `filename` 又按 string 算 less O(1)。类型不对称——如果调用方有 `std::string suffixStr`，传入时还要求隐式 `const char*` 转换。

**核心识别点：**
- 只读字符串入参用 `std::string_view`（C++17），不是 `const std::string&`。
- `string_view` 对字面量零分配、零拷贝，`.size()` 是 O(1)、`.substr()` 也是 O(1)。
- `const std::string&` 传字面量有隐形 `string` 构造（堆分配），是隐藏的性能陷阱。
- `const char*` 缺失 `.size()` 方法，只能 O(n) strlen，且 C++ 代码应避免 C 风格字符串操作。

**来源：** C++ Core Guidelines F.16（仅读字符串传 string_view）；Abseil TotW #1；cppconf "string_view" 多场。
