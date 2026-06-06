---
qid: cpp-class-med-002
type: single
kp: [cpp-classes]
difficulty: medium
answer_key: D
---

下列代码的行为是？

```cpp
class C {
public:
    C()        : C(0) {}
    C(int x)   : C(x, 0) {}
    C(int x, int y) : C() {}   // ← 形成循环
private:
    int a, b;
};
```

A. 正常编译，构造时无限递归，运行时栈溢出
B. 正常编译，编译器自动展开为默认初始化
C. 仅在调用 `C{}` 时才报错
D. 编译错误（ill-formed），委托构造形成循环

---

**解析：**

C++11 引入的**委托构造函数**（delegating constructor）规定：一组构造函数通过委托链相互调用时不能形成环。标准 [class.base.init]/9 明确"若委托构造关系形成循环，程序 ill-formed"，编译器必须诊断，无需运行时检测。

本例中 `C()` → `C(int)` → `C(int,int)` → `C()` 构成闭环，GCC/Clang 直接报 `delegation cycle`。委托构造的真正用法是把公共初始化逻辑抽到一个"主构造函数"中，其它构造函数委托到它，链条必须是有向无环图。

## 解析

正确答案为 D，因为“编译错误（ill-formed），委托构造形成循环”符合题干所问的 C++ 规则或代码执行结果。A、B、C 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。类与对象题要区分默认访问权限、对象生命周期、静态成员、const 成员函数和初始化规则。
