---
qid: cpp-poly-adv-008
type: fill
kp: [cpp-polymorphism]
difficulty: medium
answer_key: "sizeof(WithVirtual) - sizeof(WithoutVirtual) == 8（在64位平台，差值等于一个指针大小）"
---

在 64 位平台上，填写以下代码的输出结果：

```cpp
#include <iostream>

struct WithoutVirtual {
    int x;
    int y;
};

struct WithVirtual {
    virtual void f();
    int x;
    int y;
};

int main() {
    std::cout << sizeof(WithoutVirtual) << "\n";  // 输出 ___
    std::cout << sizeof(WithVirtual)    << "\n";  // 输出 ___
    std::cout << (sizeof(WithVirtual) - sizeof(WithoutVirtual)) << "\n";  // 输出 ___
}
```

填写三行输出（依次）：`___`、`___`、`___`

---

**解析：**

- `WithoutVirtual`：2 个 `int`（各 4 字节），共 8 字节，无 padding，`sizeof = 8`。
- `WithVirtual`：vptr（8 字节，64位指针）+ `int x`（4）+ `int y`（4）= 16 字节，`sizeof = 16`。
- 差值 = 16 - 8 = **8**，恰好等于一个指针的大小。

**结论**：每个含虚函数的类（及其派生类，若未再引入新的 vptr）会在对象起始处增加一个 vptr，64 位下固定开销 8 字节。这就是"虚函数空间代价"。

三行输出：`8`、`16`、`8`。

## Explanation

填空应为 `sizeof(WithVirtual) - sizeof(WithoutVirtual) == 8（在64位平台，差值等于一个指针大小）`，因为这是题干所问概念或语法在 C++ 中的标准写法。多态题的关键是区分静态类型与动态类型：只有通过基类指针或引用调用虚函数时，才会发生运行期动态分派。常见误区是把普通成员函数、对象切片、构造/析构期调用也当成完整的虚调用场景。 常见误区是写出近似术语、别名或只写部分符号；填空题通常要求与答案键精确对应。
