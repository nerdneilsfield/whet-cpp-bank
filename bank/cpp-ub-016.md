---
qid: cpp-ub-016
type: fill
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: 未定义行为
---

# 数据竞争

```cpp
#include <thread>
int counter = 0;

void inc() {
    for (int i = 0; i < 1000; ++i)
        counter++;   // 无锁并发写
}

int main() {
    std::thread t1(inc), t2(inc);
    t1.join(); t2.join();
}
```

两个线程在没有任何同步机制的情况下并发写同一变量 `counter`，这属于______。

（填：未定义行为 / 实现定义行为 / 编译错误 / 保证结果为 2000）

## Explanation

填入 `未定义行为`，因为题目要求的是该规则下的精确表达或标准名称。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 常见误区是写出近似说法、旧式写法或省略必要的命名空间/符号，导致与答案含义不完全一致。
