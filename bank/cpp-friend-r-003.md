---
qid: cpp-friend-r-003
type: single
kp: [cpp-friend]
difficulty: easy
answer_key: "C"
---

### 题目

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

## Explanation

正确答案是 C。`friend class A;` 只让 `A` 成为 `B` 的友元，所以 `A::accessB` 可以访问 `B::y`，但这不会让 `A` 自动成为 `C` 的友元。A、B 项错误地把友元权限扩展到了无关类；D 项也不对，因为这里的问题不是声明顺序，而是 `C` 从未授予 `A` 访问私有成员 `z` 的权限。
