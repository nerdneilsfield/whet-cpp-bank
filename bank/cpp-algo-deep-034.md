---
qid: cpp-algo-deep-034
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: C
---

下列代码（C++17）的结果是？

```cpp
int a = std::gcd(24, 36);
int b = std::lcm(4, 6);
std::cout << a << " " << b;
```

A. `1 24`
B. `12 0`
C. `12 12`
D. 编译错误，C++ 标准库无 gcd/lcm

---

**解析：**

C++17 在 `<numeric>` 中引入 `std::gcd` 和 `std::lcm`：

- `std::gcd(24,36) = 12`（最大公约数）
- `std::lcm(4,6)  = 12`（最小公倍数）

要求两参数为**整型**（不含 bool）。返回类型是两参数 `common_type`。

注意溢出：`lcm(a,b) = a/gcd(a,b) * b`，对大数可能溢出，标准未规定溢出处理。

C++20 还加入了 `std::midpoint(a, b)`（避免 `(a+b)/2` 的中间溢出）与 `std::lerp(a, b, t)` 等数值工具。
