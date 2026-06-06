---
qid: cpp-ub-017
type: single
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: B
---

# double-free

```cpp
int* p = new int(5);
delete p;
delete p;   // 第二次 delete
```

第二次 `delete p` 的行为是：

A. 安全，`delete` 对同一指针的第二次调用被标准允许且为空操作
B. 未定义行为（double-free），可能破坏堆结构或被利用作安全漏洞
C. 编译错误，编译器追踪所有权并拒绝二次释放
D. 运行时必然崩溃，但不是未定义行为
