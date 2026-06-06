---
qid: cpp-fp-med-003
type: single
kp: [cpp-function-pointers]
difficulty: medium
answer_key: A
---

成员函数指针的调用语法与普通函数指针不同。以下代码哪个**正确**调用了成员函数？

```cpp
struct S {
    int data = 42;
    int get() const { return data; }
};
```

A.
```cpp
auto pmf = &S::get;
S s;
int val = (s.*pmf)();
```

B.
```cpp
int (*pmf)() = &S::get;
S s;
int val = pmf();
```

C.
```cpp
auto pmf = &S::get;
S s;
int val = *pmf(s);
```

D.
```cpp
int (S::*pmf)() = &S::get;
S s;
int val = s.*pmf;  // 注意没有 ()
```

---

**解析：**

成员函数指针不是普通指针，不能隐式转换为普通函数指针。它的调用必须通过 `.*`（对象）或 `->*`（指针）操作符，并加上调用括号：

- `s.*pmf()` 或 `(s.*pmf)()` — 需要括号包围 `s.*pmf`，因为 `.*` 优先级低于 `()`。

A 正确：`auto pmf = &S::get;` 推导为 `int (S::*)() const`，`(s.*pmf)()` 正确调用。

B 错误：类型不匹配，`&S::get` 不能初始化 `int(*)()`。

C 错误：`*pmf(s)` 语法错误，`pmf(s)` 不是合法的成员指针调用。

D 错误：`s.*pmf` 没有调用括号，不会执行函数调用，只是表达式（语法错误或取地址）。

## Explanation

正确答案是 A，对应“cpp auto pmf = &S::get; S s; int val = (s.pmf)(); ”。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。其他选项容易混淆相关概念：B 项“cpp int (pmf)() = &S::get; S s; int val = pmf(); ”不满足题干要求；C 项“cpp auto pmf = &S::get; S s; int val = pmf(s); ”不满足题干要求；D 项“cpp int (S::pmf)() = &S::get; S s; int val = s.pmf; // 注意没有 () ”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
