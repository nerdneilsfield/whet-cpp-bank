---
qid: cpp-smf-013
type: single
kp: [cpp-special-members]
difficulty: easy
answer_key: D
---

以下代码能否编译通过？原因是什么？

```cpp
struct NoCopy {
    NoCopy() = default;
    NoCopy(const NoCopy&) = delete;
};

NoCopy a;
NoCopy b = a;  // 此行
```

A. 能编译，调用移动构造
B. 能编译，调用默认构造
C. 能编译，调用拷贝赋值运算符
D. 不能编译，拷贝构造已被 `= delete` 禁用
