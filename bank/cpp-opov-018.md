---
qid: cpp-opov-018
type: fill
kp: [cpp-operator-overload]
difficulty: easy
answer_key: "data[index]"
---

补全 `operator[]` 的实现，使其返回对应元素的引用：

```cpp
struct Array {
    int data[10];
    int& operator[](int index) {
        return ______;
    }
    const int& operator[](int index) const {
        return data[index];
    }
};
```

## 解析

填空应为 `data[index]`，因为这是题干所问概念或语法在 C++ 中的标准写法。运算符重载题要区分语法形式与实际调用的函数，并注意返回值、const、成员/非成员选择及内置运算符语义限制。常见误区是把重载看成改变了语言规则，或忽略临时对象、引用返回和左右操作数类型对重载解析的影响。 常见误区是写出近似术语、别名或只写部分符号；填空题通常要求与答案键精确对应。
