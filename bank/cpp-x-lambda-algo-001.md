---
qid: cpp-x-lambda-algo-001
type: single
kp: [cpp-lambdas, cpp-algorithms]
primary_kp: cpp-lambdas
difficulty: medium
answer_key: B
---

下列代码使用 lambda 给 `std::sort` 提供比较器，最可能在调试模式或某些实现下触发崩溃/断言：

```cpp
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> v{5, 3, 8, 1, 9, 4, 2};

    int count = 0;
    std::sort(v.begin(), v.end(),
              [&count](int a, int b) {
                  ++count;
                  return a <= b;       // ← 注意这里
              });
}
```

主要问题在于：

A. lambda 按引用捕获 `count`，导致数据竞争
B. 比较器使用 `<=`，不是严格弱序，违反 `std::sort` 的前提条件，行为未定义
C. lambda 不应捕获外部变量，无法用作 sort 的比较器
D. `std::sort` 要求比较器返回 `int`（负/零/正），而非 `bool`

---

## Explanation

`std::sort` 要求比较器满足 **strict weak ordering（严格弱序）**（[alg.sorting]/3），核心要求之一是 **irreflexive**：`comp(a, a) == false`。

`a <= b` 显然不满足这个要求：当 `a == b` 时，`comp(a, a) == true`。这违反了 strict weak ordering，导致 `std::sort` 的行为属于 **未定义行为**——常见表现是 libstdc++/libc++ 在 debug 模式下断言崩溃（`__glibcxx_assert`），release 模式下可能死循环、越界访问相邻内存，甚至段错误。

正确的比较器：

```cpp
return a < b;      // 升序
return a > b;      // 降序
```

也可以用 `std::less<>{}` / `std::greater<>{}` / `std::ranges::less` 等标准比较器，它们已经保证 strict weak ordering。

- **A 错**：`std::sort` 是单线程算法，不会引入数据竞争；引用捕获本身合法（虽然语义上无意义）。
- **C 错**：lambda 完全可以捕获外部变量作为 sort 比较器，标准库的 `qsort` 才需要 C 函数指针、不能捕获。
- **D 错**：标准要求比较器返回可隐式转换为 `bool` 的值。`qsort` 才用 -/0/+ 三态返回 `int`。
