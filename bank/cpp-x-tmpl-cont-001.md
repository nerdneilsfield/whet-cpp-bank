---
qid: cpp-x-tmpl-cont-001
type: single
kp: [cpp-templates, cpp-containers]
primary_kp: cpp-containers
difficulty: medium
answer_key: C
---

下列代码中，哪一行会编译失败或行为与 `std::vector<int>` 显著不同？

```cpp
#include <vector>

int main() {
    std::vector<bool> vb{true, false, true};
    std::vector<int>  vi{1, 0, 1};

    bool& br = vb[0];           // (1)
    int&  ir = vi[0];           // (2)

    auto* p1 = &vb[0];          // (3)
    auto* p2 = &vi[0];          // (4)

    for (auto& x : vb) x = !x;  // (5)
}
```

A. (1) 编译失败
B. (2) 编译失败
C. (1)(3) 编译失败/行为异常；(5) 行为异常
D. 全部正常

---

## 解析

**`std::vector<bool>` 是一个特殊模板特化**（[vector.bool]）：为了节省空间，它将每个 `bool` 压缩为 1 bit 存储。这导致它 **不满足 `vector` 的通用契约**：

- **`operator[]` 不返回 `bool&`**，而返回一个代理对象 `std::vector<bool>::reference`，该代理内部保存指向位的引用，并重载了赋值运算符。
- **不能取真正的 `bool*`**——`&vb[0]` 返回的是代理对象的地址，类型是 `std::vector<bool>::reference*`，不是 `bool*`。

逐项分析：

- **(1) `bool& br = vb[0];`** — 编译失败。`vb[0]` 返回的代理对象不能绑定到 `bool&`（除非声明 `bool&& br` 但这没意义）。正确写法是 `auto br = vb[0];`（取代理）或 `bool b = vb[0];`（取值）。
- **(2) `int& ir = vi[0];`** — 合法。`vector<int>::operator[]` 返回 `int&`。
- **(3) `auto* p1 = &vb[0];`** — `auto*` 推导出 `std::vector<bool>::reference*`，但 `&` 应用于临时代理对象，会触发警告 "taking address of temporary"，且代理对象在表达式结束时销毁，`p1` 悬空。
- **(4) `auto* p2 = &vi[0];`** — 合法，得到 `int*`。
- **(5) `for (auto& x : vb)` 中的 `x`** — `auto&` 推导为 `std::vector<bool>::reference&`，赋值 `x = !x` 通过代理改写位，**行为上正确**，但比直觉慢且容易混淆。`auto&& x` 更通用。

所以题目问 **明显失败或行为异常的**，(1) 是确凿的编译失败，(3) 是悬空指针陷阱，(5) 是行为微妙但仍正确（不算异常）。最贴近 C 的答案。

历史教训：C++ 委员会公开承认 `vector<bool>` 是 **设计错误**（design mistake）。替代方案：
- 想要 bit-packed 存储：`std::bitset<N>`（固定大小）或 boost::dynamic_bitset。
- 想要可变长度 + 真正 `bool&`：`std::vector<char>` 或 `std::deque<bool>`。