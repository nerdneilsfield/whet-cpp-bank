---
qid: cpp-opov-020
type: fill
kp: [cpp-operator-overload]
difficulty: easy
answer_key: "explicit operator bool() const { return size > 0; }"
---

为类 `Buffer` 实现一个转换运算符，使其可在 `if (buf)` 中使用（当 `size > 0` 时为真），且不允许隐式转换为 `int`，补全空白处：

```cpp
struct Buffer {
    int size;
    Buffer(int s) : size(s) {}
    ______
};

Buffer buf(10);
if (buf) { /* 应进入此分支 */ }
```

## Explanation

填空应为 `explicit operator bool() const { return size > 0; }`，因为这是题干所问概念或语法在 C++ 中的标准写法。运算符重载题要区分语法形式与实际调用的函数，并注意返回值、const、成员/非成员选择及内置运算符语义限制。常见误区是把重载看成改变了语言规则，或忽略临时对象、引用返回和左右操作数类型对重载解析的影响。 常见误区是写出近似术语、别名或只写部分符号；填空题通常要求与答案键精确对应。
