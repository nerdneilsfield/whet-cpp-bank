---
qid: cpp-move-r-004
type: single
kp: [cpp-move-semantics]
difficulty: easy
answer_key: B
---

### 题目

下面代码中 `ref` 绑定到临时对象，该临时对象的生命周期是？

```cpp
#include <iostream>
#include <string>

int main() {
    const std::string& ref = std::string("temp");
    std::cout << ref << std::endl;
    return 0;
}
```

A. 临时对象在 `ref` 初始化完成后立即销毁，`ref` 是悬空引用
B. 临时对象的生命周期延长至与 `ref` 相同（`main` 结束），输出 `temp`
C. 编译错误，不能将常量引用绑定到临时对象
D. 未定义行为，输出随机内容

## Explanation

B


C++ 规定：将**const 左值引用**（或右值引用）绑定到临时对象时，临时对象的生命周期会延长至与该引用相同。这里 `ref` 在 `main` 返回前有效，因此 `std::cout << ref` 合法，输出 `temp`。注意：此规则仅适用于直接绑定，通过函数返回引用等方式无法延长生命周期。
