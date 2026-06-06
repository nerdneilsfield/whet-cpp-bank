---
qid: cpp-cast-r-003
type: single
kp: [cpp-casting]
difficulty: easy
answer_key: C
---

### 题目

下面代码使用 C 风格转换绕过访问控制，其危险性在于什么？

```cpp
#include <iostream>

class Base {
    int secret = 99;
};

class Derived : public Base {};

class Unrelated {
public:
    int data = 0;
};

int main() {
    Derived d;
    // C 风格强制转换：把 Derived* 当作 Unrelated*
    Unrelated* p = (Unrelated*)&d;
    std::cout << p->data << std::endl;
    return 0;
}
```

A. 编译错误：不相关类型不能转换
B. 编译通过，`static_cast` 会在运行时检查类型安全
C. 编译通过，C 风格转换不做类型检查，读取的是 `Derived` 对象内存中的原始位，行为未定义
D. 编译通过，输出 `99`

## Explanation

C


C 风格转换 `(Unrelated*)&d` 等价于 `reinterpret_cast<Unrelated*>(&d)`，编译器不做任何类型安全检查，直接重新解释内存布局。`p->data` 读取的是 `Derived` 对象内存起始处的字节，解释为 `int`，结果是不确定的（取决于内存布局）。这正是 C++ 引入 `static_cast`、`dynamic_cast` 等具名转换的原因——让转换意图明确，让编译器/运行时能做适当检查，防止此类危险操作悄无声息地通过编译。
