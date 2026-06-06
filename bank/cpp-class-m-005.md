---
qid: cpp-class-m-005
type: multi
kp: [cpp-classes]
difficulty: easy
answer_key: [A, B, D]
---

关于成员初始化列表，下列哪些说法**正确**？（选择所有正确项）

```cpp
class Point {
    const int x;
    int& ref;
    int y;
public:
    Point(int a, int& r, int b) : x(a), ref(r), y(b) {}
};
```

A. `const` 成员和引用成员**必须**通过成员初始化列表初始化，不能在构造函数体内赋值
B. 成员初始化列表中的初始化顺序由**成员在类中的声明顺序**决定，与列表中的书写顺序无关
C. 使用成员初始化列表和在构造函数体内赋值对所有类型的成员效果完全相同，没有性能差异
D. 对于类类型成员，使用成员初始化列表可以直接调用合适的构造函数，避免先默认构造再赋值的额外开销
