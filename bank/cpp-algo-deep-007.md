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

## Explanation

正确答案是 B：std::generate 会对每个位置调用一次生成器，因此可得到 0 到 4。std::fill 是把同一个值赋给所有元素，不能表达逐次递增；传 lambda 也不是让它被调用。更直接的写法是 std::iota(v.begin(), v.end(), 0)。
