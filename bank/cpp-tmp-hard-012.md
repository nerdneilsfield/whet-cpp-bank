---
qid: cpp-tmp-hard-012
type: multi
kp: [cpp-templates]
difficulty: hard
answer_key: [B, D]
---

比较以下两种存储"可调用对象"的方式：

```cpp
// 方式 A：虚函数（继承方式）
struct Base { virtual void call() = 0; };
struct Impl : Base {
    void call() override { std::cout << "impl\n"; }
};

// 方式 B：类型擦除（std::function）
std::function<void()> f;
f = []() { std::cout << "lambda\n"; };
```

以下哪些说法正确？（多选）

A. 方式 A 可以直接存储 lambda，无需继承
B. 方式 B（`std::function`）可以存储任意可调用对象，包括 lambda、函数指针、仿函数
C. 方式 A 和方式 B 在运行时开销上完全相同
D. 方式 B 的类型擦除技术使调用者无需知道具体类型，方式 A 需要共同基类
