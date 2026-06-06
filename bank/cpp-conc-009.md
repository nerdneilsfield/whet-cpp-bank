---
qid: cpp-conc-009
type: single
kp: [cpp-concurrency]
difficulty: easy
answer_key: C
---

# 代码阅读：线程终止问题

```cpp
#include <thread>
void task() { /* ... */ }

int main() {
    std::thread t(task);
    return 0;  // ← 未调用 join/detach
}
```

该程序运行时会发生什么？

A. `task()` 在后台正常执行完毕  
B. 编译失败  
C. 调用 `std::terminate()`，程序异常终止  
D. `main` 等待 `task()` 结束后再退出  
