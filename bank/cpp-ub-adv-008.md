---
qid: cpp-ub-adv-008
type: single
kp: [cpp-undefined-behavior]
difficulty: medium
answer_key: B
---

下列代码通过 `reinterpret_cast` 访问 placement new 构造的对象，行为是什么？

```cpp
#include <new>

struct Point { int x, y; };

int main() {
    alignas(Point) char buf[sizeof(Point)];

    // 方式一：使用 placement new 返回的指针
    Point* p1 = new (buf) Point{1, 2};
    int a = p1->x;   // (1)

    // 方式二：通过 reinterpret_cast 访问
    Point* p2 = reinterpret_cast<Point*>(buf);
    int b = p2->x;   // (2)
}
```

A. (1) 和 (2) 都合法，结果相同
B. (1) 合法；(2) 在 C++17 之前是 UB，C++17 起因隐式生命周期对象规则可能合法
C. (2) 合法，(1) 多此一举，直接 cast 更规范
D. 两者都是 UB，必须使用 `std::launder`

---

**解析：**

**(1) `p1->x`**：placement new 返回的指针直接指向新创建的对象，访问合法。

**(2) `p2->x`**：`buf` 是 `char` 数组，`reinterpret_cast<Point*>(buf)` 只是重解释地址，**不创建对象**。

- **C++14 及之前**：对象必须由构造函数创建；`buf` 内存上已有 placement new 创建的 `Point`，但 `p2` 不是"指向该对象的指针"——严格来说需要 `std::launder(reinterpret_cast<Point*>(buf))`。
- **C++17**：引入"隐式创建对象"（implicit-lifetime types）概念：`Point` 若满足条件（POD/平凡类型），`char` 数组上的 placement new 使 `p2` 可被视为指向该对象，但仍推荐使用 `std::launder`。
- **最佳实践**：始终使用 placement new 的返回值，或使用 `std::launder`：
  ```cpp
  Point* p2 = std::launder(reinterpret_cast<Point*>(buf));  // C++17
  ```
