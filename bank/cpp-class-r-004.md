---
qid: cpp-class-r-004
type: single
kp: [cpp-classes]
difficulty: easy
answer_key: B
---

# 代码阅读：析构顺序（先派生后基类）

阅读以下代码，推断输出结果：

```cpp
#include <iostream>
struct Base {
    ~Base() { std::cout << "~Base "; }
};
struct Derived : Base {
    ~Derived() { std::cout << "~Derived "; }
};
int main() {
    Derived d;
    return 0;
}
```

A. `~Base ~Derived`  
B. `~Derived ~Base`  
C. 仅输出 `~Base`（`Derived` 析构函数未设为 `virtual`）  
D. 编译错误：析构函数必须声明为 `virtual`
