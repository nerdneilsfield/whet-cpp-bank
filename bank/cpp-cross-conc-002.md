---
qid: cpp-cross-conc-002
type: single
kp: [cpp-concurrency]
difficulty: easy
answer_key: A
---

下面两段代码，哪段**存在数据竞争**？

**代码 A（无锁）：**
```cpp
int counter = 0;
std::thread t1([&]{ for(int i=0;i<1000;i++) counter++; });
std::thread t2([&]{ for(int i=0;i<1000;i++) counter++; });
t1.join(); t2.join();
```

**代码 B（有锁）：**
```cpp
int counter = 0;
std::mutex mtx;
std::thread t1([&]{ for(int i=0;i<1000;i++){ std::lock_guard<std::mutex> lg(mtx); counter++; } });
std::thread t2([&]{ for(int i=0;i<1000;i++){ std::lock_guard<std::mutex> lg(mtx); counter++; } });
t1.join(); t2.join();
```

A. 代码 A 存在数据竞争
B. 代码 B 存在数据竞争
C. 两段代码都存在数据竞争
D. 两段代码都不存在数据竞争

> **提示：** `lock_guard` 在作用域内独占 mutex，离开作用域自动释放。无锁情况下多线程并发写同一变量是未定义行为。

## 解析

A 正确：代码 A 中两个线程同时对普通 `int counter` 执行读-改-写，没有同步，构成数据竞争，行为未定义。代码 B 用同一个 `mutex` 和 `lock_guard` 保护每次递增，临界区互斥。关键误区是以为 `counter++` 是单条语句就天然原子；它不是。
