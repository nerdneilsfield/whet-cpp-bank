---
qid: cpp-mod-multi-med-008
type: multi
kp: [cpp-cpp11]
difficulty: medium
answer_key: [A, B, D]
---
关于 C++11 范围 `for` 循环的行为，**哪些说法是正确的**？（多选）

```cpp
std::vector<bool> vb{true, false, true};
for (auto& b : vb) { b = !b; }      // (1)
for (const auto& x : getVec()) {}   // (2), getVec 返回 std::vector<int>
for (auto x : range_expr) {}        // (3) 等价于什么？
```

A. (1) 在某些实现下会编译失败，因为 `vector<bool>` 的 `operator[]` 返回代理对象，不能绑定到 `T&`
B. (2) 中，C++11 起范围 for 中的范围表达式产生的临时对象，其生命周期延长至循环结束
C. 范围 for 要求被迭代对象必须是 STL 容器，自定义类型不能使用范围 for
D. (3) 在 C++17 之前等价于 `auto&& __range = range_expr; auto __b = __range.begin(); auto __e = __range.end(); for(; __b != __e; ++__b) { auto x = *__b; ... }`

---

**解析：**

A 正确：`vector<bool>` 的迭代器解引用得到的是 `reference` 代理对象（非真正的 `bool&`），无法绑定到 `bool&`。需使用 `auto&&` 或 `auto`。
B 正确：范围 for 内部用 `auto&& __range = range_expr;` 绑定，引用绑定到右值会延长其生命周期到 `__range` 作用域结束（即整个循环）。
C 错误：只要类型满足"有 `begin()`/`end()` 成员，或可被 ADL 找到自由函数 `begin/end`"即可，C 数组、自定义类型、`std::initializer_list` 都行。
D 正确：这是标准规定的范围 for 等价展开式（C++17 之前 begin/end 必须同类型；C++17 起允许 sentinel 不同类型）。
