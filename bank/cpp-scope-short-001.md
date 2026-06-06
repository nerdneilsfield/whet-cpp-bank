---
qid: cpp-scope-short-001
type: short
kp: [cpp-scope-linkage]
difficulty: medium
rubric:
  - 区分内部链接（internal linkage）：仅在当前翻译单元可见
  - 区分外部链接（external linkage）：可被其他翻译单元引用
  - 给出实现手段：匿名命名空间或 static 让符号变为内部链接
  - 提到 const / inline / template 默认通常具有内部链接或 vague linkage
---
请解释 C++ 中"内部链接（internal linkage）"与"外部链接（external linkage）"的区别，以及如何让一个全局符号具有内部链接。

---

**参考答案：**

链接性决定符号在多个翻译单元间是否可见。外部链接（external linkage）的符号可被其他翻译单元通过同名声明访问，是默认的全局函数和全局变量的链接类型；内部链接（internal linkage）的符号仅在自己所在的翻译单元可见，链接器不会把不同 TU 的同名内部符号视作同一实体。让符号具有内部链接的常用方式：在文件作用域加 `static` 关键字，或者把它放到匿名命名空间 `namespace { ... }` 中（推荐，且对类型也有效）。`const` 全局变量在 C++ 中默认就有内部链接（与 C 不同），`inline`/template 通常采用 vague linkage 以避免重复定义错误。

## 解析

作答应围绕：区分内部链接（internal linkage）：仅在当前翻译单元可见；区分外部链接（external linkage）：可被其他翻译单元引用；给出实现手段：匿名命名空间或 static 让符号变为内部链接。作用域与链接性题要区分名字可见范围、对象生存期和跨翻译单元链接属性；三者相关但不是同一个概念。常见误区是把局部 static 的静态存储期理解成全局可见，或把遮蔽变量误认为修改了外层变量。 短答题不要只给结论，还要说明为什么这些规则会导致相应行为，并指出容易混淆的反例或边界情况。
