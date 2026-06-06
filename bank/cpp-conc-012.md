---
qid: cpp-conc-012
type: fill
kp: [cpp-concurrency]
difficulty: easy
answer_key: "2000"
---

# 代码阅读：atomic 修复计数

```cpp
std::atomic<int> counter{0};

void inc() {
    for (int i = 0; i < 1000; ++i)
        counter.fetch_add(1);
}

int main() {
    std::thread t1(inc), t2(inc);
    t1.join(); t2.join();
    std::cout << counter.load();
}
```

程序输出的值一定是 ____。
