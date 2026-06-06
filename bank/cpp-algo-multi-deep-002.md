---
qid: cpp-algo-multi-deep-002
type: multi
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: [B, C]
---

关于 `std::sort` 比较器要求，下列哪些是**严格弱序**的必要条件？（多选）

```cpp
auto cmp = [](const T& a, const T& b){ return /* ... */; };
std::sort(v.begin(), v.end(), cmp);
```

A. `cmp(a, b) ⇒ cmp(b, a)`（对称性）
B. `cmp(a, a) == false`（反自反性 / irreflexivity）
C. `cmp(a, b) && cmp(b, c) ⇒ cmp(a, c)`（传递性）
D. 必须返回 `std::strong_ordering`

## Explanation

正确选项是 B、C。严格弱序要求反自反性和传递性，还要求 cmp(a,b) 为真时 cmp(b,a) 不能同时为真；A 写成了对称性，方向正好错误。std::sort 的比较器只需可转换为 bool，不要求返回 std::strong_ordering；违反这些性质会导致排序行为不可靠。
