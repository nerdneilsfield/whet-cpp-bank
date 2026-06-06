---
qid: cpp-algo-deep-032
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: B
---

`std::iota` 的作用是？

```cpp
std::vector<int> v(5);
std::iota(v.begin(), v.end(), 10);
// v = ?
```

A. `10 10 10 10 10`
B. `10 11 12 13 14`
C. `0 1 2 3 4`
D. 把 v 反转

---

**解析：**

`std::iota(first, last, value)` 把 `[first, last)` 依次填为 `value, value+1, value+2, ...`（用 `++` 自增）。来自 APL 的同名函数。位于 `<numeric>` 头文件，而不是 `<algorithm>`。

常用场景：
- 生成下标向量：`std::vector<int> idx(n); std::iota(idx.begin(), idx.end(), 0);` 再 `std::sort(idx.begin(), idx.end(), [&](int a,int b){return arr[a]<arr[b];});` 得到"参照下标排序"
- 初始化连续 ID
- 测试数据生成

C++20 起还有 `std::ranges::iota_view`（视图）和 `std::views::iota(0, n)`。
