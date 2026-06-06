---
qid: cpp-stl-multi-med-008
type: multi
kp: [cpp-stl-basics]
difficulty: medium
answer_key: [A, B, D]
---
关于 `std::string` 操作对迭代器/引用的失效规则，**哪些说法是正确的**？（多选）

```cpp
std::string s = "hello";
auto it = s.begin() + 2;
auto& r = s[2];
```

A. `s.push_back('!')` 若导致容量增长，则所有迭代器、指针、引用全部失效
B. `s.reserve(n)` 当 `n > capacity()` 时会重新分配，使所有迭代器/引用失效
C. `s.shrink_to_fit()` 是非绑定请求，编译器/库可以选择不缩容，因此**保证**不会使迭代器失效
D. `s.insert(it, 'X')` 会使插入位置及之后的迭代器/引用失效，扩容时则全部失效

---

**解析：**

A 正确：`string` 与 `vector` 类似，扩容时进行整体拷贝/移动，所有引用失效。
B 正确：`reserve(n)` 在 `n > capacity()` 时强制重新分配，迭代器/引用全部失效；`n <= capacity()` 时是 no-op。
C 错误：`shrink_to_fit()` 是非绑定请求，但**若实现选择缩容**则会失效迭代器。标准并不保证它不会使迭代器失效；准确说法是"可能使全部迭代器/引用失效"。
D 正确：与 `vector::insert` 行为一致——不扩容则插入点之后失效；扩容则全部失效。

## Explanation

A、B、D 正确：`std::string` 的迭代器、引用和指针在重新分配时会全部失效，插入等操作还可能使插入点及之后位置失效。`reserve` 增大容量必然可能重分配，`shrink_to_fit` 虽是非绑定请求，但实现若真的缩容也会失效。常见误区是把“非绑定请求”理解成“保证不改变存储”。
