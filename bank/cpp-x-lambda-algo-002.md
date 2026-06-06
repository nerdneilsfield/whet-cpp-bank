---
qid: cpp-x-lambda-algo-002
type: single
kp: [cpp-lambdas, cpp-algorithms]
primary_kp: cpp-lambdas
difficulty: medium
answer_key: C
---

下列代码使用 `std::for_each` 累加元素：

```cpp
#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v{1, 2, 3, 4, 5};
    int sum = 0;

    auto add = [sum](int x) mutable { sum += x; };  // 按值捕获 + mutable
    std::for_each(v.begin(), v.end(), add);

    std::cout << sum << "\n";   // 输出？
}
```

A. `15`
B. `5`
C. `0`
D. 编译错误

---

## 解析

按 **值捕获** `[sum]` 时，lambda 闭包对象内部持有 `sum` 的 **拷贝**，与外部 `sum` 互不相关。`mutable` 关键字 **仅允许** lambda 内部修改这个拷贝（默认情况下按值捕获的成员是 const 的），**不会** 让修改反向写回外部变量。

加上 `std::for_each` 还会对 `add` 进行 **按值传递**——即便 lambda 内部累加成功，函数返回时这份拷贝又被销毁，外部 `sum` 始终是 0。

`std::for_each` 的返回值才是「带状态的 lambda 副本」：

```cpp
auto result = std::for_each(v.begin(), v.end(), add);
// result 内部仍持有 sum=15 的副本，但无法直接读出，除非 lambda 提供 getter
```

正确写法（任选其一）：

1. **按引用捕获**：`auto add = [&sum](int x){ sum += x; };` — 直接累加到外部。
2. **使用 `std::accumulate`**（最符合习惯）：
   ```cpp
   int sum = std::accumulate(v.begin(), v.end(), 0);
   ```
3. **C++17 后用 `std::reduce`** 支持并行执行策略。

陷阱小结：
- `mutable` ≠ 「修改外部变量」，而是「修改捕获到的副本」。
- `std::for_each(it, it, f)` 把 `f` 按值传递，**返回的 f 副本** 才包含累计状态。这一点在 C++11 引入 lambda 后特别容易踩坑。