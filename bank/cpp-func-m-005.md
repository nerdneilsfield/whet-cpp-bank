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
