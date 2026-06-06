---
qid: cpp-opov-014
type: fill
kp: [cpp-operator-overload]
difficulty: easy
answer_key: "friend std::ostream& operator<<(std::ostream& os, const MyClass& obj)"
---

为类 `MyClass` 重载输出流运算符，使 `std::cout << obj` 合法，请补全函数声明（写在类外，作为友元）：

```cpp
class MyClass {
    int val;
public:
    MyClass(int v) : val(v) {}
    ______;  // 在此声明友元
};

// 类外定义
std::ostream& operator<<(std::ostream& os, const MyClass& obj) {
    os << obj.val;
    return os;
}
```

空白处应填写什么？

## Explanation

填空应为 `friend std::ostream& operator<<(std::ostream& os, const MyClass& obj)`，因为这是题干所问概念或语法在 C++ 中的标准写法。运算符重载题要区分语法形式与实际调用的函数，并注意返回值、const、成员/非成员选择及内置运算符语义限制。常见误区是把重载看成改变了语言规则，或忽略临时对象、引用返回和左右操作数类型对重载解析的影响。 常见误区是写出近似术语、别名或只写部分符号；填空题通常要求与答案键精确对应。
