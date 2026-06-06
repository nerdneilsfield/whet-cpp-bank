---
qid: cpp-stl-hard-005
type: single
kp: [cpp-stl-basics]
difficulty: hard
answer_key: D
---

C++14 引入`透明比较器（transparent comparator）`使以下查找不再需要构造临时键：

```cpp
struct MyKey {
    std::string id;
    int version;
    bool operator<(const MyKey& o) const { /* ... */ }
};

struct Comp {
    using is_transparent = void;
    bool operator()(const MyKey& a, const std::string& b) const { /* compare */ }
    bool operator()(const std::string& a, const MyKey& b) const { /* compare */ }
};

std::set<MyKey, Comp> s;
auto it = s.find(std::string_view{"hello"});  // ①
```

① 之所以成功，原理是什么？

A. `set` 未提供 `find(std::string_view)`，不能
B. `std::string_view` 隐式转换到 `MyKey` 即可
C. 透明比较器要求两个操作数必须为同一类型，因此不适用
D. 透明比较器利用 `is_transparent` 作为标签（tag trait），激活 `set::find` 的**泛型版本**（而非 `find(const Key&)`），该版本以任何类型作为传入参数直接调用 `Comp::operator()(a, b)`。只要 `Comp` 提供跨类型的比较操作符（如 `(MyKey, string_view)` 等），就不需构造 `MyKey` 临时对象

## Explanation

C++14 引入"透明比较器"通过 `using is_transparent = void;` 标记。对于关联容器 `set` / `map` / `multiset` / `multimap`，若比较器定义了 `is_transparent`，容器会开放泛型重载的查找方法 `find` / `lower_bound` / `equal_range` / `count` 等。

传统版本 `s.find(MyKey{"hello", 0})` 需要构造完整的 `MyKey`——可能触发昂贵的字符串拷贝、compare 计算。透明版本 `s.find("hello")` 或 `s.find(string_view{"hello"})` 直接传入字符串字面量或视图，比较器内部将该类型与 `Key` 元素进行跨类型比较，完全跳过临时键的构造。这在性能敏感场景（尤其是键有大字符串或复杂比较）提升显著。前提是比较器必须**提供所有操作方向的 `operator()` 重载**。
