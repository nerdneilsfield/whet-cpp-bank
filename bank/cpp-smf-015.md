---
qid: cpp-smf-015
type: single
kp: [cpp-special-members]
difficulty: easy
answer_key: B
---

以下类定义了析构函数，下列说法正确的是？

```cpp
struct MyBuf {
    int* data;
    MyBuf() : data(new int[10]) {}
    ~MyBuf() { delete[] data; }
};

MyBuf a;
MyBuf b = std::move(a);  // 此行
```

A. 调用编译器自动生成的移动构造函数，安全接管 `data`
B. 因为用户定义了析构函数，编译器不自动生成移动构造，此行调用拷贝构造，存在浅拷贝风险
C. 不能编译，移动构造被禁用
D. 调用移动赋值运算符
