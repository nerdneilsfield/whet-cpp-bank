---
qid: cpp-mod-multi-med-002
type: multi
kp: [cpp-cpp14-17]
difficulty: medium
answer_key: [A, B, C]
---
关于 C++17 结构化绑定（structured bindings），**哪些来源是合法的**？（多选）

```cpp
#include <tuple>
#include <array>
#include <map>
struct Point { int x; int y; };
```

A. `auto [a, b] = std::make_tuple(1, 2.0);`（元组类型，通过 `std::tuple_size` / `get` 支持）
B. `Point p{1,2}; auto [x, y] = p;`（聚合类，按声明顺序绑定到非静态数据成员）
C. `int arr[3] = {1,2,3}; auto [a, b, c] = arr;`（C 数组，按元素绑定）
D. `std::map<int,int> m; for (auto [k,v] : m) {}` 中 `k` 是 `int&`，可以修改 `map` 的键

---

**解析：**

A 正确：`std::tuple`、`std::pair` 实现了 `tuple_size`/`tuple_element`/`get`，是结构化绑定的标准三种来源之一。
B 正确：聚合类（无用户提供的构造函数、无私有/受保护非静态成员、无虚基类等）可直接按声明顺序绑定数据成员。
C 正确：固定长度的 C 数组可按元素绑定，元素个数必须与绑定列表数量一致。
D 错误：`std::map<K,V>::value_type` 是 `std::pair<const K, V>`，因此 `k` 实际上是 `const int&`，不能通过它修改键。
