---
qid: cpp-friend-018
type: fill
kp: [cpp-friend]
difficulty: easy
answer_key: "不能访问，Base 的友元不是 Derived 的友元（友元不继承）"
---

阅读以下代码，回答问题：

```cpp
class Base {
    int val = 100;
    friend void baseHelper(Base& b);
};

class Derived : public Base {
    int extra = 200;
};

void baseHelper(Base& b) {
    std::cout << b.val;  // 正常
}

void test(Derived& d) {
    std::cout << d.val;  // 此处能否访问？
}
```

`test` 函数能否访问 `d.val`？为什么？（`val` 是从 `Base` 继承来的私有成员）

答：______

## 解析

应填写 `不能访问，Base 的友元不是 Derived 的友元（友元不继承）`。本题考查友元声明的访问权限规则，关键是友元只授予特定函数或类访问权，不会自动成为成员。该答案能与题干中的代码上下文、声明形式或输出结果精确匹配，因此既要关注语法位置，也要关注类型和值的含义。常见误区是写出近似形式但改变了指针/引用/捕获/格式化等语义，导致编译失败或结果不同。
