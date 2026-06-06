---
qid: cpp-bp-error-002
type: single
kp: [cpp-exceptions]
difficulty: medium
answer_key: B
---

C++23 引入 `std::expected<T, E>`。如下两种 API 设计哪种更适合"用户输入解析"这种**预期会失败**的场景？

```cpp
// 设计 A：异常
int parse_age(std::string_view s) {
    int v;
    auto [p, ec] = std::from_chars(s.data(), s.data()+s.size(), v);
    if (ec != std::errc{}) throw std::invalid_argument("not int");
    if (v < 0 || v > 150) throw std::out_of_range("bad age");
    return v;
}

// 设计 B：expected
std::expected<int, std::string> parse_age(std::string_view s) {
    int v;
    auto [p, ec] = std::from_chars(s.data(), s.data()+s.size(), v);
    if (ec != std::errc{}) return std::unexpected("not int");
    if (v < 0 || v > 150) return std::unexpected("bad age");
    return v;
}
```

A. 设计 A：异常更清晰
B. 设计 B：expected，因为失败是高频预期情况，不应承担异常的展开开销
C. 两者等价
D. 应使用 errno 类似的全局错误码

---

## 解析

C++ 异常机制采用零开销 (zero-cost) 模型——只在抛出路径才有开销，但**抛出本身的成本极高**（栈展开、RTTI 匹配、内存分配等），通常上千 CPU 周期。规则："exceptions are for exceptional cases"。

- 用户输入解析：**预期** 会失败（用户敲错很常见）→ `expected`
- 文件打开失败：**预期** 会发生 → `expected` 或 errno
- 内存分配失败、不变量被破坏：罕见且通常不可恢复 → 异常或 abort

选项 A 在用户敲错就抛异常的循环里（如批量解析 CSV），性能可下降数十倍。选项 D 的 errno 在并发与组合性上极差，几乎不可推荐于新代码。

正确做法：把 `expected` 作为新代码的默认返回类型，异常仅用于"程序员错误"（如越界、空指针）和真正罕见的系统级失败。