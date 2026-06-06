---
qid: cpp-scope-018
type: single
kp: [cpp-scope-linkage]
difficulty: easy
answer_key: A
---

# extern const 使常量具有外部链接

下列代码能让其他翻译单元访问 `MAX` 常量的**正确**做法是？

A.
```cpp
// header.h
extern const int MAX;

// defs.cpp
extern const int MAX = 100;
```

B.
```cpp
// header.h
const int MAX = 100;
```

C.
```cpp
// defs.cpp
static const int MAX = 100;
```

D.
```cpp
// defs.cpp
namespace { const int MAX = 100; }
```

选项中哪个能使 `MAX` 被多个翻译单元共享？

答：______

## 解析

本题应根据答案键 `A` 判断。作用域与链接性题要区分名字可见范围、对象生存期和跨翻译单元链接属性；三者相关但不是同一个概念。常见误区是把局部 static 的静态存储期理解成全局可见，或把遮蔽变量误认为修改了外层变量。 作答时要把规则和题干中的具体代码或描述对应起来，避免只凭表面形式选择。
