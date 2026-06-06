---
qid: cpp-friend-009
type: fill
kp: [cpp-friend]
difficulty: easy
answer_key: "friend"
---

在类内声明一个外部函数 `void show(MyClass&)` 为友元，关键字是 ______。

## Explanation

应填写 `friend`。本题考查友元声明的访问权限规则，关键是友元只授予特定函数或类访问权，不会自动成为成员。该答案能与题干中的代码上下文、声明形式或输出结果精确匹配，因此既要关注语法位置，也要关注类型和值的含义。常见误区是写出近似形式但改变了指针/引用/捕获/格式化等语义，导致编译失败或结果不同。
