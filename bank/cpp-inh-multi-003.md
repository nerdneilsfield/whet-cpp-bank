---
qid: cpp-inh-multi-003
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: A
---

```cpp
struct A { void show() { std::cout << "A"; } };
struct B { void show() { std::cout << "B"; } };
struct C : public A, public B {};

C c;
c.show(); // 这行代码会？
```

A. 编译错误：`show` 调用不明确（ambiguous）
B. 输出 "A"（优先选第一个基类）
C. 输出 "B"（优先选第二个基类）
D. 链接错误

## 解析

正确答案是 A，对应“编译错误：show 调用不明确（ambiguous）”。本题考查继承中的访问控制、构造析构顺序、虚函数或多继承规则，关键是区分静态类型限制和运行期动态绑定。其他选项容易混淆相关概念：B 项“输出 "A"（优先选第一个基类）”不满足题干要求；C 项“输出 "B"（优先选第二个基类）”不满足题干要求；D 项“链接错误”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
