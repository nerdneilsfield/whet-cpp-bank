---
qid: cpp-smf-r-003
type: single
kp: [cpp-special-members]
difficulty: easy
answer_key: "B"
---

### 题目

阅读以下代码，标注 (1)(2) 各触发的是拷贝构造还是拷贝赋值？

```cpp
#include <iostream>

struct Log {
    Log() { }
    Log(const Log&) { std::cout << "copy-ctor\n"; }
    Log& operator=(const Log&) { std::cout << "copy-assign\n"; return *this; }
};

int main() {
    Log a;
    Log b = a;   // (1)
    Log c;
    c = a;       // (2)
}
```

A. (1) 拷贝赋值，(2) 拷贝构造
B. (1) 拷贝构造，(2) 拷贝赋值
C. (1)(2) 均为拷贝构造
D. (1)(2) 均为拷贝赋值

## Explanation

(1) `Log b = a` 是**初始化**语句，`b` 此时尚未存在，调用**拷贝构造函数**，输出 `copy-ctor`。(2) `c = a` 是**赋值**语句，`c` 已经存在（由默认构造创建），调用**拷贝赋值运算符**，输出 `copy-assign`。`=` 出现在声明中是初始化（构造），出现在已有对象上是赋值——两者触发不同的特殊成员函数。
