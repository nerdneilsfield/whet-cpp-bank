---
qid: cpp-func-m-003
type: multi
kp: [cpp-functions]
difficulty: easy
answer_key: [A, B, D]
---

以下哪些情况下**引用传递**优于**值传递**？选择所有正确项。

```cpp
void process(std::vector<int>& v);   // 引用传递
void process(std::vector<int> v);    // 值传递
```

A. 参数是大型对象，需要避免拷贝开销
B. 函数需要修改调用方传入的变量
C. 参数是 `int`、`double` 等基本类型且无需修改
D. 参数是类对象且拷贝构造代价高昂

> 选择所有正确项。
