---
qid: cpp-algo-deep-037
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: hard
answer_key: C
---

下列代码 `std::priority_queue<int>` 默认是 max-heap，要改成 min-heap 应该传？

```cpp
std::priority_queue<int, std::vector<int>, ???> pq;
```

A. `std::less<int>`
B. `std::min<int>`
C. `std::greater<int>`
D. `std::not_equal_to<int>`

---

**解析：**

`std::priority_queue` 的比较器语义有些反直觉：**比较器返回 `true` 表示"前者应排在后者之后"（即"优先级更低"）**。

- 默认 `std::less<T>`：当 `a < b` 为真，`a` 优先级更低 → `b` 在堆顶 → **max-heap**
- `std::greater<T>`：当 `a > b` 为真，`a` 优先级更低 → 小的在堆顶 → **min-heap**

`std::make_heap` 等底层算法用法相同：传 `std::greater` 得 min-heap。

记忆：与 `std::sort` 的"`less` → 升序，`greater` → 降序"是**反过来的**——因为 priority_queue 取的是末尾的最大值作堆顶。
