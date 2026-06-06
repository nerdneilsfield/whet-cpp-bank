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

## 解析

正确答案是 C。`thread_local` 对每个线程提供独立对象实例，不能把它当作普通共享全局变量。选项 C 的表述“0”正好符合该规则。A、B、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。 进一步判断时要回到题干给出的具体代码、接口名和标准语义，避免用相似概念的经验结论替代本题要求。
