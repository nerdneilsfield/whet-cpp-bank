---
qid: cpp-conc-adv-002
type: single
kp: [cpp-concurrency]
difficulty: easy
answer_key: C
---

以下代码中，线程 A 将 `x` 设为 1，线程 B 将 `x` 设为 2，执行完毕后主线程读取 `x` 的可能结果是？

```cpp
thread_local int x = 0;

void threadA() { x = 1; }
void threadB() { x = 2; }

int main() {
    std::thread ta(threadA);
    std::thread tb(threadB);
    ta.join(); tb.join();
    std::cout << x << std::endl; // 主线程读自己的 x
}
```

A. 1
B. 2
C. 0
D. 未定义行为，结果不确定
