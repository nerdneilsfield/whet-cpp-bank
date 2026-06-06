---
qid: cpp-scope-015
type: fill
kp: [cpp-scope-linkage]
difficulty: easy
answer_key: "1 2"
---

# mutable 成员在 const 函数中修改

阅读以下代码，填写输出结果（两个数用空格分隔）：

```cpp
#include <iostream>

struct Counter {
    mutable int calls = 0;
    int value;

    Counter(int v) : value(v) {}

    int get() const {
        ++calls;
        return value;
    }
};

int main() {
    const Counter c(42);
    c.get();
    c.get();
    std::cout << c.calls << "\n";   // 行 A

    Counter d(10);
    d.get();
    std::cout << d.calls << "\n";   // 行 B

    return 0;
}
```

行 A 和行 B 的输出依次是 ______。
