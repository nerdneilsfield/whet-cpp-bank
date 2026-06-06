---
qid: cpp-class-med-008
type: single
kp: [cpp-classes]
difficulty: medium
answer_key: B
---

下列 C++11 起的代码，最后一行 `std::cout << u.i;` 的行为是？

```cpp
union U {
    int   i;
    float f;
};

U u;
u.f = 1.0f;        // 激活成员变为 f
std::cout << u.i;  // ← 通过非激活成员读取
```

A. 良构，输出 1
B. 未定义行为：读取的不是当前激活的成员
C. 实现定义：等价于位级 reinterpret
D. 编译错误，union 不允许浮点成员

---

**解析：**

C++ 标准只允许通过**当前激活成员**读取 union 的值。`u.f = 1.0f` 把激活成员设为 `f`，再读 `u.i` 属于读取非激活成员，行为未定义（[class.union.general]/2）。

这一点与 C 语言不同：C99/C11 允许通过 union 做"类型双关"（type-punning），但 C++ 始终把这种读法视为 UB，编译器在优化时可以假设 `u.i` 与 `u.f` 不指向同一对象。

正确的做位级转换的方法：

```cpp
int bits;
std::memcpy(&bits, &u.f, sizeof(bits));   // C++03 起合法
int bits2 = std::bit_cast<int>(u.f);      // C++20
```

GCC/Clang 作为扩展容忍 union 类型双关，但写可移植代码时不应依赖。

## Explanation

正确答案为 B，因为“未定义行为：读取的不是当前激活的成员”符合题干所问的 C++ 规则或代码执行结果。A、C、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。类与对象题要区分默认访问权限、对象生命周期、静态成员、const 成员函数和初始化规则。
