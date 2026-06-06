---
qid: cpp-move-r-005
type: single
kp: [cpp-move-semantics]
difficulty: easy
answer_key: B
---

### 题目

对 `const` 对象调用 `std::move`，实际会触发哪个构造函数？

```cpp
#include <iostream>
#include <string>

int main() {
    const std::string a = "hello";
    std::string b = std::move(a);   // 对 const 对象 move
    std::cout << "a=" << a << " b=" << b << std::endl;
    return 0;
}
```

A. 移动构造，`a` 变为空，输出 `a= b=hello`
B. 拷贝构造，`a` 不变，输出 `a=hello b=hello`
C. 编译错误，`const` 对象不能 `std::move`
D. 未定义行为

## Explanation

B


`std::move(a)` 将 `a` 转换为 `const std::string&&`。但 `std::string` 的移动构造函数签名为 `string(string&&)`，无法绑定 `const` 右值引用——它需要可修改的对象才能"窃取"资源。重载决议退而选择拷贝构造 `string(const string&)`，因此发生的是**拷贝**而非移动：`a` 内容不变，`b` 得到副本，输出 `a=hello b=hello`。对 `const` 对象 `std::move` 是常见误用，不会有编译错误，但也没有性能收益。
