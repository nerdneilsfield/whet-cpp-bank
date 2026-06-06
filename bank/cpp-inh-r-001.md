---
qid: cpp-inh-r-001
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: "C"
---

## 题目

阅读以下代码，程序输出是什么？

```cpp
#include <iostream>

struct Animal {
    std::string name = "Animal";
    void speak() { std::cout << "..."; }
};

struct Dog : Animal {
    std::string name = "Dog";
    void speak() { std::cout << "Woof"; }
};

int main() {
    Dog d;
    Animal a = d;      // 对象切片
    std::cout << a.name << std::endl;
    a.speak();
    std::cout << std::endl;
}
```

A. `Dog` 然后 `Woof`
B. 编译错误：不能将 `Dog` 赋值给 `Animal`
C. `Animal` 然后 `...`
D. `Dog` 然后 `...`

## 解析

`Animal a = d` 发生**对象切片（object slicing）**：只有 `Animal` 的部分被复制，`Dog` 特有的 `name` 和 `speak` 被丢弃。`a.name` 是 `Animal` 的成员，值为 `"Animal"`；`a.speak()` 调用 `Animal::speak`，输出 `...`。这是非虚函数 + 值语义下切片的典型陷阱。
