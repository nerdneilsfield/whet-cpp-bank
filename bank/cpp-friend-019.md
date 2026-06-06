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
