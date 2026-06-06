---
qid: cpp-tmpl-adv-009
type: single
kp: [cpp-templates]
difficulty: easy
answer_key: A
---

以下用可变参数模板递归展开的 `print` 函数，正确的实现模式是？

A.
```cpp
void print() {}  // 递归终止：空参数包

template<typename T, typename... Rest>
void print(T first, Rest... rest) {
    std::cout << first << "\n";
    print(rest...);  // 递归展开
}
```

B.
```cpp
template<typename... Args>
void print(Args... args) {
    std::cout << args << "\n";  // 直接展开，不递归
}
```

C.
```cpp
template<typename... Args>
void print(Args... args) {
    for (auto a : args) std::cout << a << "\n";  // range-for 展开
}
```

D.
```cpp
template<typename T>
void print(T first, T... rest) {  // 所有参数必须同类型
    std::cout << first;
    print(rest...);
}
```
