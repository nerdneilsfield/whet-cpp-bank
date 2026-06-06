---
qid: cpp-algo-fill-deep-006
type: fill
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: ["std::iota", "iota", "std::ranges::iota"]
---

要把 `std::vector<int> v(5)` 填充为 `0, 1, 2, 3, 4`，最简洁的标准算法调用是 `_______(v.begin(), v.end(), 0);`。

---

**解析：**

`std::iota(first, last, start)`（`<numeric>`）依次写入 `start, start+1, start+2, ...`（通过 `operator++`）。

替代方案：
- `std::generate(v.begin(), v.end(), [n=0]() mutable { return n++; });`
- C++20 ranges：`std::ranges::copy(std::views::iota(0, 5), v.begin());`

`std::fill` 只能填同一个值；`std::iota` 才是"递增序列"。

常用习语：生成 `idx = {0..n-1}` 再按外部值排序：
```cpp
std::vector<int> idx(arr.size());
std::iota(idx.begin(), idx.end(), 0);
std::sort(idx.begin(), idx.end(),
          [&](int a, int b){ return arr[a] < arr[b]; });
```
