---
qid: cpp-algo-deep-040
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: hard
answer_key: C
---

下列代码（C++17）使用执行策略并行求和，**风险**是？

```cpp
std::vector<int> v(1'000'000, 1);
long long sum = 0;
std::for_each(std::execution::par, v.begin(), v.end(),
              [&](int x){ sum += x; });
std::cout << sum;
```

A. 安全；`for_each` 自动加锁
B. 编译错误
C. **数据竞争（data race）**，对 `sum` 的并发非原子写是 UB；正确做法是用 `std::reduce`
D. 输出固定为 0

---

**解析：**

`std::execution::par` 允许并行执行 lambda，但**不提供同步**——程序员必须保证谓词/函数对象**无数据竞争**。多线程同时执行 `sum += x` 是经典数据竞争 → UB（结果可能远小于 1'000'000）。

正确并行加和：

```cpp
auto sum = std::reduce(std::execution::par, v.begin(), v.end(), 0LL);
```

或用 `std::atomic<long long>` / `std::transform_reduce`。

另一坑：`par_unseq` 还允许**矢量化交错执行**，谓词中不可调用同步原语（mutex、I/O 等），违反同样是 UB。
