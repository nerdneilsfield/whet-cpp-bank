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

## Explanation

正确答案是 C：C++17 在 <numeric> 中提供 std::gcd 和 std::lcm。24 与 36 的最大公约数是 12，4 与 6 的最小公倍数也是 12，所以输出 `12 12`。误区是以为这些数值工具不在标准库，或忽略 lcm 在大整数上可能溢出。
