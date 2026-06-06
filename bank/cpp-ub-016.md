---
qid: cpp-ub-016
type: fill
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: 未定义行为
---

# 数据竞争

```cpp
#include <thread>
int counter = 0;

void inc() {
    for (int i = 0; i < 1000; ++i)
        counter++;   // 无锁并发写
}

int main() {
    std::thread t1(inc), t2(inc);
    t1.join(); t2.join();
}
```

两个线程在没有任何同步机制的情况下并发写同一变量 `counter`，这属于______。

（填：未定义行为 / 实现定义行为 / 编译错误 / 保证结果为 2000）
