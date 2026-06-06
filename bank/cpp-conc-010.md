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

## Explanation

正确答案是 B。并发题的核心是同步关系、数据竞争和原子/锁的适用边界。选项 B 的表述“不确定，可能小于 2000（存在数据竞争）”正好符合该规则。A、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。 进一步判断时要回到题干给出的具体代码、接口名和标准语义，避免用相似概念的经验结论替代本题要求。
