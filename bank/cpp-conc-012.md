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

## Explanation

应填 `2000`。`std::atomic` 保证单个对象的原子访问，但是否提供同步还取决于所用内存序。 这个答案对应题干要求的标准名称、成员函数或复杂度写法。常见误区是填写相近但语义不同的接口，或漏掉作用域、大小写、下划线等精确拼写要求。 进一步判断时要回到题干给出的具体代码、接口名和标准语义，避免用相似概念的经验结论替代本题要求。
