---
qid: cpp-algo-deep-007
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: B
---

下列两段代码哪段能**正确**填满 `v` 为 `[0,1,2,3,4]`？

```cpp
std::vector<int> v(5);
// (1) std::fill(v.begin(), v.end(), [n=0]() mutable { return n++; });
// (2) std::generate(v.begin(), v.end(), [n=0]() mutable { return n++; });
```

A. 只有 (1) 正确
B. 只有 (2) 正确
C. 两者都正确
D. 两者都错误

---

**解析：**

`std::fill(first, last, value)` 把每个元素赋值为**同一个 value**；传入 lambda 会把 lambda 对象本身赋给元素（若元素类型不接受 lambda 则编译错误）。

`std::generate(first, last, gen)` 调用**无参生成器** `gen()` 为每个位置生成一个值，正合需要。还有 `std::iota(v.begin(), v.end(), 0)` 是更直接的等差填充。

若要把所有元素填成同一常量，用 `std::fill`；若要让每个位置不同，用 `std::generate` 或 `std::iota`。
