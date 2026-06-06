---
qid: cpp-smf-r-004
type: single
kp: [cpp-special-members]
difficulty: easy
answer_key: "C"
---

### 题目

阅读以下代码，运行后输出的析构顺序是什么？

```cpp
#include <iostream>

struct A { ~A() { std::cout << "~A\n"; } };
struct B { ~B() { std::cout << "~B\n"; } };
struct C { ~C() { std::cout << "~C\n"; } };

struct Obj {
    A a;
    B b;
    C c;
};

int main() {
    Obj obj;
}
```

A. `~A` → `~B` → `~C`
B. 顺序不确定
C. `~C` → `~B` → `~A`
D. `~Obj` → `~A` → `~B` → `~C`

## Explanation

正确答案是 C，成员对象的析构顺序与声明顺序相反。`Obj` 的成员按 `a, b, c` 构造，销毁时先销毁 `c`，再销毁 `b`，最后销毁 `a`。这与成员在构造函数初始化列表中的书写顺序无关，常见误区是按初始化列表或字母顺序判断。 这类题的关键是区分语法形式、对象生命周期和所有权语义：语法看似相近时，应先判断谁拥有资源、表达式值类别是什么，以及标准是否保证该行为；不要根据实现习惯或表面写法推断答案。
