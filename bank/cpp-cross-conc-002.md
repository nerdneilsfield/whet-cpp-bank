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
