---
qid: cpp-conc-010
type: single
kp: [cpp-concurrency]
difficulty: easy
answer_key: B
---

# 代码阅读：数据竞争

```cpp
int counter = 0;

void inc() {
    for (int i = 0; i < 1000; ++i)
        ++counter;  // 无同步
}

int main() {
    std::thread t1(inc), t2(inc);
    t1.join(); t2.join();
    // counter 的值是多少？
}
```

`counter` 的最终值是？

A. 一定是 2000  
B. 不确定，可能小于 2000（存在数据竞争）  
C. 一定是 1000  
D. 编译器会自动生成原子指令，结果为 2000  
