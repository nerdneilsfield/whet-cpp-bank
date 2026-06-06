---
qid: cpp-poly-adv-003
type: single
kp: [cpp-polymorphism]
difficulty: medium
answer_key: A
---

以下代码使用 CRTP 实现 `Comparable` mixin，`a < b` 的结果是什么？

```cpp
#include <iostream>

template <typename Derived>
struct Comparable {
    bool operator<(const Derived& other) const {
        return static_cast<const Derived*>(this)->compare(other) < 0;
    }
};

struct Point : Comparable<Point> {
    int val;
    explicit Point(int v) : val(v) {}
    int compare(const Point& other) const {
        return val - other.val;
    }
};

int main() {
    Point a{3}, b{7};
    std::cout << (a < b) << "\n";
}
```

A. 输出 `1`（即 `true`，因为 3 < 7）
B. 输出 `0`（因为 `compare` 返回负数，`operator<` 逻辑反转）
C. 编译错误：`Comparable` 无法访问 `Derived::compare`
D. 未定义行为：`static_cast` 在 `operator<` 中不安全

---

**解析：**

`Comparable<Point>::operator<` 内调用 `static_cast<const Point*>(this)->compare(other)`，返回 `3 - 7 = -4`（< 0），所以 `operator<` 返回 `true`，输出 `1`。

CRTP mixin 是添加通用运算符的经典手法：
- `Comparable` 只需要派生类实现 `compare()`，自动获得 `<`、`>`、`<=`、`>=` 等运算符。
- `static_cast` 在 CRTP 中安全：`this` 所指对象的动态类型**必然**是 `Derived`（否则代码根本无法实例化）。

## Explanation

正确答案是 A，因为该选项对应 `输出 `1`（即 `true`，因为 3 < 7）`，符合题中代码或概念的 C++ 语义。多态题的关键是区分静态类型与动态类型：只有通过基类指针或引用调用虚函数时，才会发生运行期动态分派。常见误区是把普通成员函数、对象切片、构造/析构期调用也当成完整的虚调用场景。 B 项、C 项、D 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
