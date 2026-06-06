---
qid: cpp-scope-009
type: fill
kp: [cpp-scope-linkage]
difficulty: easy
answer_key: "3"
---

# static 局部变量计数

阅读以下代码，填写程序的输出结果：

```cpp
#include <iostream>

void counter() {
    static int n = 0;
    ++n;
    std::cout << n << "\n";
}

int main() {
    counter();
    counter();
    counter();
    return 0;
}
```

程序依次输出三行，第三行的值是 ______。
