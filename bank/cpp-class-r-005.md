---
qid: cpp-class-r-005
type: single
kp: [cpp-classes]
difficulty: easy
answer_key: C
---

# 代码阅读：对象按值传参触发拷贝构造

阅读以下代码，推断输出结果：

```cpp
#include <iostream>
struct Widget {
    Widget() { std::cout << "ctor "; }
    Widget(const Widget&) { std::cout << "copy "; }
    ~Widget() { std::cout << "dtor "; }
};
void use(Widget w) {}
int main() {
    Widget a;
    use(a);
    return 0;
}
```

A. `ctor dtor dtor`  
B. `ctor copy dtor`  
C. `ctor copy dtor dtor`  
D. `ctor dtor`
