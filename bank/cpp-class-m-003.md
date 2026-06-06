---
qid: cpp-class-m-003
type: multi
kp: [cpp-classes]
difficulty: easy
answer_key: [B, C, D]
---

关于类的静态成员，下列哪些说法**正确**？（选择所有正确项）

```cpp
class MyClass {
public:
    static int count;
    static void printCount() {
        // std::cout << this->count;  // (1)
        std::cout << count;           // (2)
    }
};
int MyClass::count = 0;
```

A. 静态成员变量在每个对象中各有一份独立的拷贝
B. 静态成员变量必须在类外进行定义和初始化（如 `int MyClass::count = 0;`）
C. 静态成员函数没有 `this` 指针，因此第 (1) 行注释掉的写法非法
D. 静态成员既可以通过类名（`MyClass::count`）访问，也可以通过对象访问
