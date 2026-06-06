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

## 解析

正确答案为 A、B、D。A项“`const` 成员函数不能修改普通数据成员，但可以修改 `mutable` 成员（如第 (1) 行合法）”是正确项；B项“`const` 对象只能调用 `const` 成员函数”是正确项；C项“`const` 成员函数内部可以调用该类的任意其他成员函数（包括非 `const` 成员函数）”不是正确项；D项“在 `const` 成员函数中，`this` 指针的类型是指向 `const` 对象的指针”是正确项。常见误区是只看到相似术语就全选，实际应逐项检查标准规则和题干限定。类与对象题要区分默认访问权限、对象生命周期、静态成员、const 成员函数和初始化规则。
