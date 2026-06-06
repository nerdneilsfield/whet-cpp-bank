---
qid: cpp-bp-init-002
type: single
kp: [cpp-classes]
difficulty: medium
answer_key: C
---

下列代码输出的 vector 元素个数和值是？

```cpp
#include <vector>
#include <iostream>

int main() {
    std::vector<int> a(3, 5);      // (1)
    std::vector<int> b{3, 5};      // (2)
    std::vector<int> c = {3, 5};   // (3)
    std::vector<int> d{3};         // (4)
    std::vector<int> e(3);         // (5)

    std::cout << a.size() << " " << b.size() << " "
              << c.size() << " " << d.size() << " " << e.size() << "\n";
}
```

A. 3 3 3 3 3
B. 3 2 2 1 3
C. 3 2 2 1 3，且 b/c/d 的内容是 {3,5}、{3,5}、{3}
D. 编译错误

---

## Explanation

`vector` 同时有 `vector(size_t count, T value)` 和 `vector(initializer_list<T>)` 两个构造，**花括号永远优先匹配 initializer_list 重载**。

逐个分析：
1. `a(3, 5)` → 圆括号，size=3 重复填充 5 → `{5, 5, 5}`，size = 3
2. `b{3, 5}` → 花括号匹配 initializer_list<int> → `{3, 5}`，size = **2**
3. `c = {3, 5}` → 同上，size = 2
4. `d{3}` → 匹配 initializer_list → `{3}`，size = **1**（注意不是 size=3 的空 vector）
5. `e(3)` → 圆括号，size=3 用 T{} (= 0) 填充 → `{0, 0, 0}`，size = 3

这是 C++11 引入 initializer_list 后最大的陷阱之一。规则："**brace init prefers initializer_list when present**"。

工程教训：对于**有 initializer_list 构造的容器类**（vector、list、deque、map），区分 size+value 和 init-list 时必须用圆括号；否则容易引入"应该 1000 个 0，实际只有 1 个 1000"的 bug。

```cpp
std::vector<int> buf(1024);     // 1024 个 0   ← 想要的
std::vector<int> bug{1024};     // 1 个 1024   ← bug！
```

对自定义类，C++17 后建议同时提供两种构造时仔细考虑命名（如 `make_vector_filled` 工厂）。
