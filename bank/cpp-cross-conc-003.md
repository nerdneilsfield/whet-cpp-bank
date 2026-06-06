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

## 解析

答案是 `2000`。`std::atomic<int>` 的自增是原子读-改-写操作，两个线程各执行 1000 次递增，每一次更新都会被完整记录，不会互相覆盖。关键误区是把普通 int 的数据竞争问题套到 atomic 上；这里没有数据竞争，最终结果确定。
