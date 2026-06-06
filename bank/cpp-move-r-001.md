---
qid: cpp-move-r-001
type: single
kp: [cpp-move-semantics]
difficulty: easy
answer_key: B
---

## 题目

下面代码输出什么？

```cpp
#include <iostream>
#include <string>

int main() {
    std::string a = "hello";
    std::string b = std::move(a);
    std::cout << "a=" << a << " b=" << b << std::endl;
    return 0;
}
```

A. `a=hello b=hello`
B. `a= b=hello`
C. `a=hello b=`
D. 编译错误

## 答案

B

## 解析

`std::move(a)` 将 `a` 转换为右值引用，触发 `std::string` 的移动构造函数。移动后，`b` 获得原字符串内容 `"hello"`，而 `a` 处于合法但未指定（valid-but-unspecified）状态——对于标准库 `std::string` 的典型实现，移后对象变为空字符串。因此输出 `a= b=hello`。
