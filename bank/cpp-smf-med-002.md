---
qid: cpp-smf-med-002
type: single
kp: [cpp-special-members]
difficulty: medium
answer_key: B
---

下列两种禁止拷贝的写法在错误诊断质量上有何差别？

```cpp
// 方式①：C++03 的 private 未定义法
class NoCopy1 {
public:
    NoCopy1() = default;
private:
    NoCopy1(const NoCopy1&);             // 只声明不定义
    NoCopy1& operator=(const NoCopy1&);
};

// 方式②：C++11 的 = delete
class NoCopy2 {
public:
    NoCopy2() = default;
    NoCopy2(const NoCopy2&)            = delete;
    NoCopy2& operator=(const NoCopy2&) = delete;
};

void user(NoCopy1 a, NoCopy2 b) {
    NoCopy1 c = a;
    NoCopy2 d = b;
}
```

A. 两者完全等价，任何时候都给出一样的错误
B. 方式① 在友元/成员函数内调用拷贝时只在链接阶段报错；方式② 在编译阶段直接报错
C. 方式① 是 C++ 标准禁止的写法，无法通过编译
D. 方式② 只能用在类外，类内必须用方式①

---

**解析：**

方式①（private + 只声明不定义）是 C++03 时代的惯用法（出自 Boost `noncopyable`）。在类外调用拷贝会触发**编译期**“访问私有成员”错误；但若在**类的成员函数或友元**内拷贝，访问检查通过，会生成对未定义函数的调用，错误推迟到**链接期**才以“undefined reference”出现，信息含糊难定位。

方式②（`= delete`）的关键改进：函数仍然参与重载决议，只是被选中后立即在编译期报“use of deleted function”，且与访问性无关——无论 public、private、成员、友元，全部在调用点就被拒绝，错误信息清晰指向源行。

因此现代 C++（C++11 起）应一律使用 `= delete`，并放在 public 区段，因为访问检查发生在 deleted 检查之前；放 public 能让错误信息直接说“deleted”而不是误导性的“private”。

## 解析

正确答案是 B，private 未定义法在类外通常报访问错误，但在成员或友元内部访问合法，可能拖到链接期才因缺少定义失败。`= delete` 则在重载决议选中时立即于编译期报“use of deleted function”，诊断更直接。现代 C++ 应优先使用 `= delete` 表达禁止调用的意图。
