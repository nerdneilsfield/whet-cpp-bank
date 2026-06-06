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

## Explanation

正确答案是 B：(a + b) / 2 会先计算 int 加法，超过范围时带符号溢出，行为未定义，常见表现可能是负数。std::midpoint 专门避免中间加法溢出，能得到 INT_MAX - 1。二分搜索或区间算法中计算中点时，应优先使用这种安全写法。
