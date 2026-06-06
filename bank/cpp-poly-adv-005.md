---
qid: cpp-poly-adv-005
type: single
kp: [cpp-polymorphism]
difficulty: medium
answer_key: C
---

以下 CRTP 实例计数器代码，`main` 结束时 `Circle::count` 和 `Square::count` 分别是多少？

```cpp
#include <iostream>

template <typename Derived>
struct Counter {
    static int count;
    Counter()  { ++count; }
    ~Counter() { --count; }
};
template <typename Derived>
int Counter<Derived>::count = 0;

struct Circle : Counter<Circle> {};
struct Square : Counter<Square> {};

int main() {
    Circle c1, c2, c3;
    Square s1;
    {
        Circle c4;
        Square s2, s3;
    }
    std::cout << Circle::count << " " << Square::count << "\n";
}
```

A. `4 3`（作用域内对象未析构）
B. `3 1`（所有对象均已析构，计数清零）
C. `3 1`（`c4/s2/s3` 离开内层作用域析构，剩余 `c1 c2 c3` 和 `s1`）
D. `0 0`（`count` 是 `static`，程序结束时自动归零）

---

**解析：**

- `Counter<Circle>` 和 `Counter<Square>` 各有独立的静态成员 `count`，两者互不干扰——这是 CRTP 实例计数的核心优势。
- 外层作用域：`Circle c1, c2, c3`（count=3），`Square s1`（count=1）。
- 内层作用域：`Circle c4`（count→4），`Square s2, s3`（count→3）；内层作用域结束后 `c4/s2/s3` 析构，`Circle::count→3`，`Square::count→1`。
- `main` 结束时输出 `3 1`。

注意 B 和 C 的答案数字相同，但 B 的解释错误（析构并非使计数清零，而是逐步递减）。正确选项是 C。

## Explanation

正确答案是 C，因为该选项对应 ``3 1`（`c4/s2/s3` 离开内层作用域析构，剩余 `c1 c2 c3` 和 `s1`）`，符合题中代码或概念的 C++ 语义。多态题的关键是区分静态类型与动态类型：只有通过基类指针或引用调用虚函数时，才会发生运行期动态分派。常见误区是把普通成员函数、对象切片、构造/析构期调用也当成完整的虚调用场景。 A 项、B 项、D 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
