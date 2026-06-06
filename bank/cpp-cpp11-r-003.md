---
qid: cpp-cpp11-r-003
type: single
kp: [cpp-cpp11]
difficulty: easy
answer_key: "D"
---

## 题目

阅读以下代码，编译结果是什么？

```cpp
struct NoCopy {
    NoCopy() = default;
    NoCopy(const NoCopy&) = delete;
    NoCopy& operator=(const NoCopy&) = delete;
};

int main() {
    NoCopy a;
    NoCopy b = a;  // 行 A
    NoCopy c;
    c = a;         // 行 B
}
```

A. 编译通过，运行正常
B. 仅行 A 处编译错误
C. 仅行 B 处编译错误
D. 行 A 和行 B 均编译错误

## 解析

`= delete` 显式删除拷贝构造函数和拷贝赋值运算符。行 A `NoCopy b = a` 调用拷贝构造函数（已删除），行 B `c = a` 调用拷贝赋值运算符（已删除），两处均会触发编译错误，提示 "use of deleted function"。答案 D。
