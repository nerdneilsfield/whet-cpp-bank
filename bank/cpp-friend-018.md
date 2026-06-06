---
qid: cpp-friend-018
type: fill
kp: [cpp-friend]
difficulty: easy
answer_key: "不能访问，Base 的友元不是 Derived 的友元（友元不继承）"
---

阅读以下代码，回答问题：

```cpp
class Base {
    int val = 100;
    friend void baseHelper(Base& b);
};

class Derived : public Base {
    int extra = 200;
};

void baseHelper(Base& b) {
    std::cout << b.val;  // 正常
}

void test(Derived& d) {
    std::cout << d.val;  // 此处能否访问？
}
```

`test` 函数能否访问 `d.val`？为什么？（`val` 是从 `Base` 继承来的私有成员）

答：______
