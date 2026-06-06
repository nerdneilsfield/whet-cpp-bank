---
qid: cpp-tmpl-r-003
type: single
kp: [cpp-templates]
difficulty: easy
answer_key: B
---

### 题目

下面代码输出是什么？

```cpp
#include <iostream>
#include <string>

template<typename T>
class Box {
public:
    T value;
    Box(T v) : value(v) {}
    void show() { std::cout << value << std::endl; }
};

int main() {
    Box<int> a(42);
    Box<std::string> b("hello");
    a.show();
    b.show();
    return 0;
}
```

A. 编译错误：类模板不能存储不同类型
B. 输出：`42` 和 `hello`
C. 输出：`42` 和 `0`
D. 输出：`0` 和 `hello`

## Explanation

B


`Box<int>` 和 `Box<std::string>` 是同一类模板的两个独立实例化，分别生成针对 `int` 和 `std::string` 的具体类。`a.show()` 输出 `42`，`b.show()` 输出 `hello`。类模板实例化后的两个类型完全独立，`Box<int>` 和 `Box<std::string>` 之间没有任何继承或转换关系。
