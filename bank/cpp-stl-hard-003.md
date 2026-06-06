---
qid: cpp-stl-hard-003
type: single
kp: [cpp-stl-basics]
difficulty: hard
answer_key: C
---

`std::vector<bool>` 的特化与其他 `vector<T>` 的关键区别是什么？

```cpp
std::vector<bool> vb{true, false, true};
auto x = vb[0];          // x 的类型？
bool* p = &vb[0];        // ① 能编译？
vb.reserve(100);         // ② 能编译？
```

关于以上代码的说法，最准确的是？

A. `vb[0]` 返回 `bool&`，一切正常
B. `vector<bool>` 不是真正的容器，但以上调用都合法
C. `std::vector<bool>` 是唯一一个标准库**特化**模板——它将每个 `bool` 压缩为 1 位（bit）。`operator[]` 不返回 `bool&`（无法引用单个位），而返回 `std::vector<bool>::reference`（代理对象）。① `&vb[0]` 得不到 `bool*`；② `reserve` 无法预留"位"；标准 23.3.12 明确说 `vector<bool>` "不满足容器的所有要求"
D. `vector<bool>` 自 C++23 起被移除

## 解析

`std::vector<bool>` 是 `std::vector<bool>` 的全特化，存储紧凑的位字段，每字节 8 个元素。为此付出了代价：它的 `iterator` 不是随机访问迭代器的完全模型（实际上是随机访问迭代器，但 `*it` 返回代理而非 `bool&`），`operator[]` 返回类 `std::vector<bool>::reference`（一个代理对象），不能取地址、不能绑定到 `bool&`。因此 `auto x = vb[0]` 中 `x` 的类型是 `std::vector<bool>::reference`，而非 `bool`。`&vb[0]` 编译失败无法获得 `bool*`。C++ 标准承认 `vector<bool>` 是"准容器"，不是完全容器。若需要可寻址的 `bool` 容器，应使用 `deque<bool>` 或 `std::vector<char>`。