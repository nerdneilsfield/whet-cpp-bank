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

## 解析

正确答案是 A、C。`std::atomic` 保证单个对象的原子访问，但是否提供同步还取决于所用内存序。 A 正确：｀x.store(5)｀ 原子地将 ｀x｀ 设为 5；B 错误：｀x.load()｀ 返回值不一定是 5，因为有数据竞争；C 正确：｀x.fetch_add(3)｀ 原子地将 ｀x｀ 加 3，返回加法前的旧值；D 错误：以上操作等价于普通的 ｀x = 5; v = x; x += 3;｀，没有本质区别；E 错误：｀std::atomic｀ 操作比 ｀mutex｀ 加锁更慢，不推荐使用。常见误区是只记住术语名称，而忽略每个选项中的限定条件、生命周期、同步关系或复杂度前提。
