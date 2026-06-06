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

## 解析

正确答案是 B。`std::future` 表示异步结果，`get()` 通常会等待就绪且结果只能取一次。选项 B 的表述“42”正好符合该规则。A、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。 进一步判断时要回到题干给出的具体代码、接口名和标准语义，避免用相似概念的经验结论替代本题要求。
