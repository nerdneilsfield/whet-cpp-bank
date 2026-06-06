---
qid: cpp-friend-r-003
type: single
kp: [cpp-friend]
difficulty: easy
answer_key: "C"
---

## 题目

阅读以下代码，编译结果是什么？

```cpp
class C {
    int z = 7;
};

class B {
    int y = 5;
    friend class A;   // A 是 B 的 friend
};

class A {
public:
    void accessB(B& b) {
        int val = b.y;   // OK：A 是 B 的 friend
    }
    void accessC(C& c) {
        int val = c.z;   // ???
    }
};
```

A. 编译通过，`accessC` 中 `c.z` 可正常访问
B. 编译通过，但 `c.z` 的值未定义
C. 编译错误：`A` 不是 `C` 的 friend，无法访问 `C::z`
D. 编译错误：friend 声明顺序有误

## 解析

friend 关系**不传递**。`A` 是 `B` 的 friend，`B` 不是 `C` 的 friend，更不存在 A→C 的 friend 关系。因此 `A::accessC` 访问 `C::z`（private 成员）会导致编译错误。
