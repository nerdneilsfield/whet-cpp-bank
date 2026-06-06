---
qid: cpp-algo-deep-029
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: hard
answer_key: B
---

下列代码的输出是？

```cpp
std::vector<int> v{1, 2, 3, 4};
auto sum1 = std::accumulate(v.begin(), v.end(), 0);     // init=0 (int)
auto sum2 = std::accumulate(v.begin(), v.end(), 0.5);   // init=0.5 (double)
std::cout << sum1 << " " << sum2;
```

A. `10 10.5`，但 `sum1` 类型是 `double`
B. `10 10.5`，`sum1` 类型是 `int`（由初始值类型决定）
C. `10 10`，两者都截断为 int
D. `10.5 10.5`

---

**解析：**

`std::accumulate` 的**累加器类型由初始值的类型决定**，与容器元素类型**无关**。原型：

```cpp
template<class It, class T>
T accumulate(It first, It last, T init);
```

经典坑：对 `vector<double>` 误传 `0`（int）会把所有部分和截成 int，导致精度丢失。

```cpp
std::vector<double> w{0.1, 0.2, 0.3};
auto bad  = std::accumulate(w.begin(), w.end(), 0);     // 0！
auto good = std::accumulate(w.begin(), w.end(), 0.0);   // 0.6
```

总要**写对初值类型**：`0.0` / `0LL` / `std::string{}` 等。
