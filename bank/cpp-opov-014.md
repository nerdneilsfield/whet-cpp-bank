---
qid: cpp-opov-014
type: fill
kp: [cpp-operator-overload]
difficulty: easy
answer_key: "friend std::ostream& operator<<(std::ostream& os, const MyClass& obj)"
---

为类 `MyClass` 重载输出流运算符，使 `std::cout << obj` 合法，请补全函数声明（写在类外，作为友元）：

```cpp
class MyClass {
    int val;
public:
    MyClass(int v) : val(v) {}
    ______;  // 在此声明友元
};

// 类外定义
std::ostream& operator<<(std::ostream& os, const MyClass& obj) {
    os << obj.val;
    return os;
}
```

空白处应填写什么？
