---
qid: cpp-cross-ms-001
type: single
kp: [cpp-move-semantics, cpp-special-members]
difficulty: easy
answer_key: B
---

以下代码输出是什么？

```cpp
#include <iostream>
#include <vector>

struct MyClass {
    MyClass() { std::cout << "ctor\n"; }
    MyClass(const MyClass&) { std::cout << "copy\n"; }
    // 显式定义了拷贝构造 → 移动构造不自动生成
};

int main() {
    std::vector<MyClass> v;
    v.reserve(2);
    MyClass a;
    v.push_back(std::move(a));  // 期望移动，但无移动构造
}
```

A. `ctor` `move`  
B. `ctor` `copy`  
C. `ctor` （无后续输出）  
D. 编译错误

<!--
显式定义了拷贝构造后，编译器不再隐式生成移动构造（Rule of 0/5）。
push_back(std::move(a)) 的实参是右值引用，但重载决议找不到移动构造，
回退到拷贝构造（const MyClass& 可绑定右值），所以输出 copy。
-->
