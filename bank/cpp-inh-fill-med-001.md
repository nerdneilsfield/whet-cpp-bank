---
qid: cpp-inh-fill-med-001
type: fill
kp: [cpp-inheritance]
difficulty: medium
answer_key: "final"
---
C++11 用 ___ 关键字阻止继续派生。

---

**解析：**

`final` 可修饰类或虚函数。用于类时表示禁止被继承；用于虚函数时表示禁止被派生类重写。它是 C++11 引入的上下文关键字，仅在成员函数声明或类声明后出现时才具有特殊含义。`final` 类的对象仍可正常构造和使用。