---
qid: cpp-poly-013
type: single
kp: [cpp-polymorphism]
difficulty: easy
answer_key: C
---

# 以下代码能否编译通过？若不能，原因是什么？

```cpp
struct Animal {
    virtual void speak() = 0;
};
int main() {
    Animal a;   // 尝试实例化抽象类
}
```

A. 可以编译，`Animal` 只是有一个纯虚函数，不影响实例化  
B. 可以编译，但运行时会崩溃  
C. 编译错误：`Animal` 是抽象类，不能直接实例化  
D. 编译错误：`speak` 没有函数体，必须提供实现
