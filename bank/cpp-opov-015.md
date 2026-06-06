---
qid: cpp-opov-015
type: single
kp: [cpp-operator-overload]
difficulty: easy
answer_key: D
---

下列代码有什么问题？

```cpp
class MyStr {
    std::string data;
public:
    std::ostream& operator<<(std::ostream& os) const {
        os << data;
        return os;
    }
};

MyStr s;
std::cout << s;  // 这行
```

A. 没有问题，语法完全正确
B. 问题在于返回类型应为 `void`
C. 问题在于 `data` 是私有成员
D. `operator<<` 定义为成员函数后，调用方式变为 `s << std::cout`，`std::cout << s` 无法匹配
