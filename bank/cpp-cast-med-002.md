---
qid: cpp-cast-med-002
type: single
kp: [cpp-casting]
difficulty: medium
answer_key: B
---

下列通过 `void*` 进行往返转换的代码，哪一个是良定义行为？

```cpp
int   i = 42;
float f = 1.5f;
void* p = &i;

// A: 把存 int* 的 void* 转回 float*
float* pf = static_cast<float*>(p);
float  x  = *pf;

// B: 把存 int* 的 void* 转回原类型 int*
int*   pi = static_cast<int*>(p);
int    y  = *pi;

// C: 把存 int* 的 void* 转成 char* 再当 long* 解
char*  pc = static_cast<char*>(p);
long*  pl = reinterpret_cast<long*>(pc);
long   z  = *pl;
```

A. 只有 A 合法
B. 只有 B 合法
C. A 和 B 都合法
D. B 和 C 都合法

---

**解析：**

`static_cast` 在 `T*` 与 `void*` 之间往返时，只有当从 `void*` 转回的目标类型与最初存入的原始类型（忽略 cv 限定）一致时，结果才是“指回原对象”的有效指针。其他类型的往返虽语法合法，但解引用得到的是 UB（违反 strict aliasing）。

B 中 `p` 原本由 `int*` 转来，再 `static_cast<int*>(p)` 拿回的就是 `&i`，`*pi` 合法。

A 把存了 `int*` 的 `void*` 当成 `float*`，类型不匹配，`*pf` 是 UB。C 经由 `char*` 中转再 reinterpret 为 `long*`，同样违反 aliasing，`*pl` 也是 UB——`char*` 中转只在“反方向”（读原对象的字节）才安全。

## Explanation

正确答案为 B，因为“只有 B 合法”符合题干所问的 C++ 规则或代码执行结果。A、C、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。类型转换题要区分编译期转换、运行期检查、cv 限定和底层位模式重解释。
