---
qid: cpp-class-m-002
type: multi
kp: [cpp-classes]
difficulty: easy
answer_key: [A, B, D]
---

关于 `const` 成员函数，下列哪些说法**正确**？（选择所有正确项）

```cpp
class Counter {
    int count = 0;
    mutable int accessCount = 0;
public:
    int get() const {
        ++accessCount;  // (1)
        return count;   // (2)
    }
};
```

A. `const` 成员函数不能修改普通数据成员，但可以修改 `mutable` 成员（如第 (1) 行合法）
B. `const` 对象只能调用 `const` 成员函数
C. `const` 成员函数内部可以调用该类的任意其他成员函数（包括非 `const` 成员函数）
D. 在 `const` 成员函数中，`this` 指针的类型是指向 `const` 对象的指针
