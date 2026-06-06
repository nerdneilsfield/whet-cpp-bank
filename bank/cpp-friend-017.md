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
