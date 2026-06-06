---
qid: cpp-friend-017
type: single
kp: [cpp-friend]
difficulty: easy
answer_key: C
---

阅读以下代码，判断哪行会导致编译错误：

```cpp
class Base {
    int secret = 42;
    friend void peek(Base& b);
};

class Derived : public Base {
};

void peek(Base& b) { std::cout << b.secret; }  // 行1
void hack(Derived& d) { std::cout << d.secret; }  // 行2

int main() {
    Base b; Derived d;
    peek(b);   // 行3
    hack(d);   // 行4
}
```

A. 行1，`peek` 不能访问 `Base::secret`
B. 行3，调用方式错误
C. 行2（`hack` 函数），`hack` 不是 `Base` 或 `Derived` 的友元
D. 行4，不能将 `Derived` 传给普通函数

## Explanation

正确答案是 C，对应“行2（hack 函数），hack 不是 Base 或 Derived 的友元”。本题考查友元声明的访问权限规则，关键是友元只授予特定函数或类访问权，不会自动成为成员。其他选项容易混淆相关概念：A 项“行1，peek 不能访问 Base::secret”不满足题干要求；B 项“行3，调用方式错误”不满足题干要求；D 项“行4，不能将 Derived 传给普通函数”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
