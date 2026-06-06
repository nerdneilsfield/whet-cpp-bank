---
qid: cpp-algo-deep-035
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: hard
answer_key: B
---

下列代码（C++20）输出是？

```cpp
int a = INT_MAX;
int b = INT_MAX - 2;
int m1 = (a + b) / 2;
int m2 = std::midpoint(a, b);
std::cout << m1 << " " << m2;
```

A. 都输出 `INT_MAX - 1`
B. `m1` 是负数（带符号溢出 UB），`m2` 正确得 `INT_MAX - 1`
C. 都输出 `INT_MAX`
D. 编译错误

---

**解析：**

`(a + b) / 2` 中 `a + b` 是 `int + int`，对带符号整型**溢出是 UB**——实际常表现为绕回为负数。

`std::midpoint(a, b)`（C++20，`<numeric>`）保证：
- 不会内部溢出
- 对整型按"向 a 截断"舍入（精确到 1）
- 对浮点保持数值稳定
- 对指针返回中点（要求指向同一数组）

经典应用：二分搜索中的中位下标计算应改用 `std::midpoint(lo, hi)` 避免 `(lo+hi)/2` 在大数组上的溢出，这是 Joshua Bloch "Almost All Binary Searches Are Broken" 的 Java 翻版问题。
