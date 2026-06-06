---
qid: cpp-cross-conc-003
type: fill
kp: [cpp-concurrency]
difficulty: easy
answer_key: "2000"
---

以下代码执行完毕后，`counter` 的值是多少？

```cpp
#include <atomic>
#include <thread>

int main() {
    std::atomic<int> counter{0};
    std::thread t1([&]{ for(int i=0;i<1000;i++) counter++; });
    std::thread t2([&]{ for(int i=0;i<1000;i++) counter++; });
    t1.join();
    t2.join();
    // counter = ?
    return 0;
}
```

请填写 `counter` 的确定值：___

> **提示：** `std::atomic<int>` 的 `++` 是原子操作，不存在竞争，每次自增都被完整记录。
