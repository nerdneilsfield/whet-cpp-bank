---
qid: cpp-func-m-005
type: multi
kp: [cpp-functions]
difficulty: easy
answer_key: [A, B, D]
---

关于 C++ **`static` 局部变量**，选择所有正确项。

```cpp
void counter() {
    static int count = 0;
    ++count;
    std::cout << count << "\n";
}
```

A. `static` 局部变量只在第一次执行到其声明时初始化一次
B. `static` 局部变量的生命周期持续到程序结束
C. 每次函数调用都会重新初始化 `static` 局部变量
D. `static` 局部变量存储在静态存储区，而不是栈上

> 选择所有正确项。

## 解析

本题正确答案是 A, B, D。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。A 项正确：“static 局部变量只在第一次执行到其声明时初始化一次”符合题干要求；B 项正确：“static 局部变量的生命周期持续到程序结束”符合题干要求；C 项错误：“每次函数调用都会重新初始化 static 局部变量”与题干要求或 C++ 规则不符；D 项正确：“static 局部变量存储在静态存储区，而不是栈上”符合题干要求。多选题常见误区是漏选同时成立的规则，或把只在特定上下文成立的说法当成普遍规则。
