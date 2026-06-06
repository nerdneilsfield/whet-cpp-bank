---
qid: cpp-conc-013
type: single
kp: [cpp-concurrency]
difficulty: easy
answer_key: D
---

# 代码阅读：`unique_lock` 手动解锁

```cpp
std::mutex mtx;
int shared = 0;

void worker() {
    std::unique_lock<std::mutex> ul(mtx);
    shared = 42;
    ul.unlock();          // ← 提前释放
    // 做一些不需要锁的耗时操作
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}
```

关于 `ul.unlock()` 的描述，正确的是？

A. `lock_guard` 也支持这样的提前 `unlock()` 调用  
B. 调用后 `ul` 析构时会再次 `unlock()`，导致未定义行为  
C. 这行代码多余，`unique_lock` 析构时会自动处理  
D. 提前释放锁，让其他线程可以更早获取锁，减少等待时间

## Explanation

正确答案是 D。互斥量通过临界区保护共享状态，适合多步复合操作而不只是单个原子读写。选项 D 的表述“提前释放锁，让其他线程可以更早获取锁，减少等待时间”正好符合该规则。A、B、C 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
