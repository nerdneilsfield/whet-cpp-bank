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

## 解析

正确答案是 B，用户定义析构函数会抑制隐式移动构造的生成，因此 `std::move(a)` 找不到移动构造时会退回可绑定右值的拷贝构造。默认拷贝会浅拷贝裸指针，两个对象析构时可能重复 `delete[] data`。这正是 Rule of Three/Five 要解决的问题。
