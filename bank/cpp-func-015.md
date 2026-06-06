---
qid: cpp-func-015
type: single
kp: [cpp-functions]
difficulty: easy
answer_key: D
---

以下代码输出什么？

```cpp
void greet() {
    std::cout << "Hello";
    return;
    std::cout << "World";
}
int main() { greet(); }
```

A. `HelloWorld`
B. `World`
C. 编译错误，`void` 函数不能有 `return`
D. `Hello`
