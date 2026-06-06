---
qid: cpp-real-quiz-030
type: single
kp: [cpp-classes, cpp-arrays-pointers]
primary_kp: cpp-classes
difficulty: hard
answer_key: B
tags: [interview-real, cppquiz, language-lawyer]
---
根据 C++17 标准，以下程序的行为是？

```cpp
#include <iostream>
struct Packed {
    unsigned a : 3;
    unsigned b : 5;
};
int main() {
    Packed p{};
    auto* pa = &p.a;        // (1)
    std::cout << "ok";
}
```

A. 输出 `ok`，`pa` 是 `unsigned*`
B. (1) 处编译错误：不能对位域取地址
C. 输出 `ok`，但 `pa` 指向 byte 中的高位/低位实现定义
D. 行为未定义

---

**解析：**

[class.bit]/3：

> A non-static data member that is a bit-field shall not have its address taken; an address-of operator applied to a bit-field is ill-formed.

位域不占有可寻址的字节（多个位域被打包进同一个存储单元），无法生成 `T*` 指针。编译器直接拒绝：

```
error: cannot take the address of a bit-field 'p.Packed::a'
```

允许的操作：
- 按值读 / 赋值：`p.a = 5;`，`unsigned x = p.a;`
- **绑定到 const 引用**：[class.bit]/4 允许 `const unsigned& r = p.a;` 但会创建一个临时（不是真的别名）
- 不允许：`&p.a`、`unsigned& r = p.a;`

这就是为什么位域不能用普通 `T*`/`T&` 抽象，也不能放进容器（迭代器解引用通常返回 T&）。`std::vector<bool>` 用代理类 `vector<bool>::reference` 模拟这种语义就是这个原因。

**来源：** C++17 [class.bit]/3