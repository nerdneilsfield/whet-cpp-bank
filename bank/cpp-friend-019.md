---
qid: cpp-friend-019
type: fill
kp: [cpp-friend]
difficulty: easy
answer_key: "编译失败，A 是 B 的友元不代表 B 是 A 的友元（友元不对称）"
---

阅读以下代码，判断是否能编译通过并说明原因：

```cpp
class B;

class A {
    int a_val = 1;
public:
    friend class B;  // B 是 A 的友元
    void readB(B& b);
};

class B {
    int b_val = 2;
    // 注意：这里没有声明 A 为友元
};

void A::readB(B& b) {
    std::cout << b.b_val;  // A 的成员函数访问 B 的私有成员
}
```

能否编译通过？原因：______

## Explanation

应填写 `编译失败，A 是 B 的友元不代表 B 是 A 的友元（友元不对称）`。本题考查友元声明的访问权限规则，关键是友元只授予特定函数或类访问权，不会自动成为成员。该答案能与题干中的代码上下文、声明形式或输出结果精确匹配，因此既要关注语法位置，也要关注类型和值的含义。常见误区是写出近似形式但改变了指针/引用/捕获/格式化等语义，导致编译失败或结果不同。
