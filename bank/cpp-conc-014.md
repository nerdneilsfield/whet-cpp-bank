---
qid: cpp-conc-014
type: single
kp: [cpp-concurrency]
difficulty: easy
answer_key: B
---

# 代码阅读：`std::async` 与 `future`

```cpp
#include <future>
#include <iostream>

int compute() { return 6 * 7; }

int main() {
    std::future<int> f = std::async(std::launch::async, compute);
    int result = f.get();
    std::cout << result;
}
```

程序的输出是？

A. 0  
B. 42  
C. 编译错误  
D. 未定义，取决于线程调度  
