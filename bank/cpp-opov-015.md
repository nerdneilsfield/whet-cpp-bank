---
qid: cpp-opov-015
type: single
kp: [cpp-operator-overload]
difficulty: easy
answer_key: D
---

下列代码有什么问题？

```cpp
class MyStr {
    std::string data;
public:
    std::ostream& operator<<(std::ostream& os) const {
        os << data;
        return os;
    }
};

MyStr s;
std::cout << s;  // 这行
```

A. 没有问题，语法完全正确
B. 问题在于返回类型应为 `void`
C. 问题在于 `data` 是私有成员
D. `operator<<` 定义为成员函数后，调用方式变为 `s << std::cout`，`std::cout << s` 无法匹配

## 解析

正确答案是 D，因为该选项对应 ``operator<<` 定义为成员函数后，调用方式变为 `s << std::cout`，`std::cout << s` 无法匹配`，符合题中代码或概念的 C++ 语义。运算符重载题要区分语法形式与实际调用的函数，并注意返回值、const、成员/非成员选择及内置运算符语义限制。常见误区是把重载看成改变了语言规则，或忽略临时对象、引用返回和左右操作数类型对重载解析的影响。 A 项、B 项、C 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
