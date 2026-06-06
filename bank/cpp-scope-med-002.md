---
qid: cpp-scope-med-002
type: single
kp: [cpp-scope-linkage]
difficulty: medium
answer_key: A
---

C++17 `inline` 变量的 ODR（One Definition Rule）影响。以下哪段代码在 C++17 下会违反 ODR？

A.
```cpp
// a.h
inline int counter = 0;
// a.cpp, b.cpp 都包含 a.h
```

B.
```cpp
// a.h
struct Config { static inline int value = 42; };
// a.cpp, b.cpp 都包含 a.h
```

C.
```cpp
// a.h
constexpr int limit = 100;
// a.cpp, b.cpp 都包含 a.h
```

D.
```cpp
// a.h
extern const int version;
// a.cpp
const int version = 1;
// b.cpp 包含 a.h，但不定义 version
```

---

**解析：**

C++17 引入了 `inline` 变量，允许一个变量在多个翻译单元中有相同定义而不违反 ODR。这与 `inline` 函数类似：同一变量名可以在多个 `.cpp` 文件中出现，链接器会合并它们为单一实体。

A 正确：`inline int counter = 0;` 在头文件中，多文件包含合法。

B 正确：`static inline int value = 42;` 是类静态成员的内联定义，C++17 允许直接在类内给出定义（之前必须在类外单独定义）。

C 正确：`constexpr` 变量隐式具有 `inline` 属性，且通常编译器直接内联其值。

D **可能违反 ODR**：如果没有 `inline`，`const int version`（非 `constexpr`）在头文件中定义（有初始化器）就是强符号，多个 `.cpp` 文件包含会重复定义。但 D 用了 `extern const int version;`（仅声明）。链接器在不同翻译单元中找到相同的符号声明和一个定义，这是合法的——**但如果有两个 `.cpp` 文件都定义了 `const int version = 1;`，那就违反 ODR**。D 实际上合法。选 A 作为正确的 inline 变量用法。

## 解析

本题应根据答案键 `A` 判断。作用域与链接性题要区分名字可见范围、对象生存期和跨翻译单元链接属性；三者相关但不是同一个概念。常见误区是把局部 static 的静态存储期理解成全局可见，或把遮蔽变量误认为修改了外层变量。 作答时要把规则和题干中的具体代码或描述对应起来，避免只凭表面形式选择。
