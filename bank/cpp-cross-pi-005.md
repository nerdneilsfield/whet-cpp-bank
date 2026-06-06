---
qid: cpp-cross-pi-005
type: single
kp: [cpp-polymorphism, cpp-inheritance]
difficulty: easy
answer_key: C
---

以下代码的输出是什么？

```cpp
#include <iostream>
#include <vector>
#include <memory>

struct Shape {
    virtual std::string name() const = 0;  // 纯虚函数
    virtual ~Shape() = default;
};

struct Circle : Shape {
    std::string name() const override { return "Circle"; }
};

struct Square : Shape {
    std::string name() const override { return "Square"; }
};

struct Triangle : Shape {
    std::string name() const override { return "Triangle"; }
};

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>());
    shapes.push_back(std::make_unique<Square>());
    shapes.push_back(std::make_unique<Triangle>());

    for (const auto& s : shapes) {
        std::cout << s->name() << "\n";
    }
    return 0;
}
```

A. 编译错误，抽象类不能放入 vector  
B. 三行都输出 `Shape`  
C. Circle / Square / Triangle（各占一行）  
D. 未定义行为

<!--
Shape 是抽象类（含纯虚函数），不能直接实例化，但可以持有其指针/智能指针。
vector 存的是 unique_ptr<Shape>，指向的是 Circle/Square/Triangle 具体对象。
name() 是 virtual，循环调用时动态分派到各自的 override，依次输出
Circle、Square、Triangle。
这是工厂模式 + 多态的典型用法。
-->

## Explanation

C 正确：`Shape` 是抽象类，不能直接创建对象，但 `vector` 存的是 `unique_ptr<Shape>`，指向具体派生对象。`name()` 是虚函数，循环中分别分派到 `Circle`、`Square`、`Triangle` 的实现。关键误区是认为抽象类不能作为指针或智能指针的静态类型。
