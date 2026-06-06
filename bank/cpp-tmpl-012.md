---
qid: cpp-tmpl-012
type: single
kp: [cpp-templates]
difficulty: easy
answer_key: D
---

# 编译错误判断

```cpp
template<typename T>
void print(T val) {
    std::cout << val << std::endl;
}

print("hello");
print(42);
print(3.14);
```

下列说法正确的是？

A. 三次调用都会编译错误，因为类型不同
B. 只有 `print("hello")` 会编译错误
C. 只有 `print(3.14)` 会编译错误
D. 三次调用都能正确编译，T 分别推导为 `const char*`、`int`、`double`
