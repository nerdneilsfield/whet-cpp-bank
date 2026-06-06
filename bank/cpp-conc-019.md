---
qid: cpp-conc-019
type: multi
kp: [cpp-concurrency]
difficulty: easy
answer_key: [A, C]
---

# 代码阅读：`std::atomic` 操作

```cpp
std::atomic<int> x{0};
x.store(5);
int v = x.load();
x.fetch_add(3);
```

以下说法**正确**的有（多选）：

A. `x.store(5)` 原子地将 `x` 设为 5  
B. `x.load()` 返回值不一定是 5，因为有数据竞争  
C. `x.fetch_add(3)` 原子地将 `x` 加 3，返回加法前的旧值  
D. 以上操作等价于普通的 `x = 5; v = x; x += 3;`，没有本质区别  
E. `std::atomic` 操作比 `mutex` 加锁更慢，不推荐使用  
