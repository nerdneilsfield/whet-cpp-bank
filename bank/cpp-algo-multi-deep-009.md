---
qid: cpp-algo-multi-deep-009
type: multi
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: [A, C]
---

关于 `std::priority_queue`，下列哪些**正确**？（多选）

```cpp
std::priority_queue<int> pq;
```

A. 默认底层容器是 `std::vector`，使用 `<algorithm>` 的堆函数维持堆性质
B. 默认是 min-heap
C. 传入 `std::greater<T>` 作为比较器可得到 min-heap
D. 支持任意迭代器遍历内部所有元素

---

**解析：**

- A ✅：声明 `priority_queue<T, Container=vector<T>, Compare=less<T>>`，内部以 `make_heap`/`push_heap`/`pop_heap` 维护。
- B ❌：默认 `std::less<T>` → max-heap（最大值在 top）。
- C ✅：`priority_queue<T, vector<T>, greater<T>>` → min-heap。
- D ❌：`priority_queue` 是适配器，只暴露 `top` / `push` / `pop` / `size` / `empty`，**没有迭代器**。要遍历需自己用 vector + heap 函数。

注：自定义对象做优先队列元素时，比较器逻辑容易写反——记住"比较器返回 true 表示前者优先级**更低**"。
