---
qid: cpp-inh-multi-003
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: A
---

```cpp
struct A { void show() { std::cout << "A"; } };
struct B { void show() { std::cout << "B"; } };
struct C : public A, public B {};

C c;
c.show(); // 这行代码会？
```

A. 编译错误：`show` 调用不明确（ambiguous）
B. 输出 "A"（优先选第一个基类）
C. 输出 "B"（优先选第二个基类）
D. 链接错误
