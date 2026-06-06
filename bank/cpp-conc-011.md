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

## 解析

正确答案是 A。互斥量通过临界区保护共享状态，适合多步复合操作而不只是单个原子读写。选项 A 的表述“一定是 2000”正好符合该规则。B、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。 进一步判断时要回到题干给出的具体代码、接口名和标准语义，避免用相似概念的经验结论替代本题要求。
