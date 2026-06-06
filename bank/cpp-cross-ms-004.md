---
qid: cpp-cross-ms-004
type: single
kp: [cpp-move-semantics, cpp-special-members]
difficulty: easy
answer_key: B
---

以下代码输出是什么？

```cpp
#include <iostream>

struct Obj {
    Obj() {}
    Obj(const Obj&)  { std::cout << "copy\n"; }
    Obj(Obj&&)       { std::cout << "move\n"; }
};

void sink(Obj o) {}

int main() {
    const Obj x;
    sink(std::move(x));   // 对 const 对象调用 std::move
}
```

A. `move`  
B. `copy`  
C. 无输出  
D. 编译错误

<!--
std::move(x) 将 x 转型为 const Obj&&（右值引用，但保留 const）。
移动构造的签名是 Obj(Obj&&)，参数是非 const 右值引用，无法绑定 const Obj&&。
拷贝构造的签名是 Obj(const Obj&)，const 左值引用可以绑定 const 右值引用（标准允许）。
因此重载决议选中拷贝构造，输出 copy。
-->
