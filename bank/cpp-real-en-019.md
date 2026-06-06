---
qid: cpp-real-en-019
type: single
kp: [cpp-classes]
primary_kp: cpp-classes
difficulty: easy
answer_key: A
tags: [interview-real, interviewbit]
---
在 C++ 中，封装（encapsulation）如何实现？封装与抽象（abstraction）的区别是什么？

A. 封装通过访问控制（`private` / `protected` / `public`）隐藏实现细节，数据成员通常设为 private 并通过公有接口访问；抽象通过纯虚函数只暴露接口不暴露实现
B. 封装就是抽象，两者在实际代码中没有区别
C. 封装是指将函数定义放在头文件中，抽象是指将实现放在 .cpp 文件中
D. 封装通过 `friend` 关键字实现，抽象通过 `virtual` 关键字实现

---

**解析：**

- **封装（Encapsulation）**：将数据和操作数据的方法捆绑在类中，通过 `private` / `protected` / `public` 访问控制隐藏内部状态。外部只能通过公有接口（getter / setter / 方法）操作对象。代码层面体现为成员变量放在 `private` 区域。
- **抽象（Abstraction）**：隐藏复杂实现细节，只暴露必要接口。C++ 中通过包含纯虚函数的抽象类实现。调用者只需知道接口签名，无需了解具体实现。

两者关系：封装是**实现手段**（如何隐藏），抽象是**设计目标**（隐藏什么）。封装帮助实现抽象。

**来源：** InterviewBit "C++ Interview Questions" — Encapsulation vs Abstraction

## Explanation

正确答案是 A。
封装（Encapsulation）：将数据和操作数据的方法捆绑在类中，通过 private / protected / public 访问控制隐藏内部状态；外部只能通过公有接口（getter / setter / 方法）操作对象。
代码层面体现为成员变量放在 private 区域；抽象（Abstraction）：隐藏复杂实现细节，只暴露必要接口。
