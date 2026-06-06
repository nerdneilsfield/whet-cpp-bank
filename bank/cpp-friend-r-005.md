---
qid: cpp-friend-r-005
type: single
kp: [cpp-friend]
difficulty: easy
answer_key: "A"
---

## 题目

阅读以下代码，程序输出是什么？

```cpp
#include <iostream>

class Wallet {
    int balance = 100;
    friend class Bank;
};

class Bank {
public:
    void deposit(Wallet& w, int amount) {
        w.balance += amount;
    }
    void withdraw(Wallet& w, int amount) {
        w.balance -= amount;
    }
    void print(const Wallet& w) {
        std::cout << w.balance << std::endl;
    }
};

int main() {
    Wallet w;
    Bank b;
    b.deposit(w, 50);
    b.withdraw(w, 30);
    b.print(w);
}
```

A. `120`
B. `100`
C. 编译错误：只有部分成员函数可以访问 private
D. `80`

## 解析

`Bank` 被声明为 `Wallet` 的 friend 类，因此 `Bank` 的**所有成员函数**都可以访问 `Wallet` 的 private 成员 `balance`。初始值 100，存入 50 后为 150，取出 30 后为 120，输出 `120`。friend 类授权是整体的，不区分成员函数。
