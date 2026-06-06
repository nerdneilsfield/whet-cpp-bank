---
qid: cpp-tmp-hard-010
type: single
kp: [cpp-templates]
difficulty: hard
answer_key: A
---

以下代码展示 `std::any` 的典型用法：

```cpp
#include <any>
#include <iostream>

int main() {
    std::any a = 42;
    a = std::string("hello");
    std::cout << std::any_cast<std::string>(a) << std::endl;

    // 尝试错误的类型转换
    try {
        int x = std::any_cast<int>(a);
    } catch (const std::bad_any_cast& e) {
        std::cout << "caught" << std::endl;
    }
}
```

程序输出是？

A. `hello` 然后 `caught`
B. `hello` 然后 `42`
C. 编译错误，`std::any` 不支持赋值不同类型
D. `hello` 然后什么都不输出（`bad_any_cast` 未被捕获）
