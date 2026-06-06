---
qid: cpp-types-med-002
type: single
kp: [cpp-types]
difficulty: medium
answer_key: B
---
下列代码哪一行会导致编译错误？

```cpp
int main() {
    double d = 3.14;
    int a = d;          // (1)
    int b{d};           // (2)
    int c = (int)d;     // (3)
    int e = static_cast<int>(d); // (4)
    return 0;
}
```

A. (1)
B. (2)
C. (3)
D. (4)

---

**解析：**

C++11 引入的列表初始化（braced-init）禁止窄化转换（narrowing conversion）。`double` 转 `int` 会丢失小数部分，属于窄化，因此 `int b{d};` 必须报错（或至少诊断为 ill-formed）。其它三种写法都是“常规”赋值或显式转换，编译器不要求禁止窄化。这正是推荐使用大括号初始化的原因之一：能在编译期捕获潜在的精度丢失。
