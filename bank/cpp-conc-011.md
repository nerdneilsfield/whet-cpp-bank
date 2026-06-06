---
qid: cpp-conc-011
type: single
kp: [cpp-concurrency]
difficulty: easy
answer_key: A
---

# 代码阅读：mutex 修复数据竞争

```cpp
std::mutex mtx;
int counter = 0;

void inc() {
    for (int i = 0; i < 1000; ++i) {
        std::lock_guard<std::mutex> lg(mtx);
        ++counter;
    }
}

int main() {
    std::thread t1(inc), t2(inc);
    t1.join(); t2.join();
}
```

`counter` 的最终值是？

A. 一定是 2000  
B. 不确定，可能小于 2000  
C. 一定是 1000  
D. 程序可能死锁  
