---
qid: cpp-io-med-001
type: single
kp: [cpp-io]
difficulty: medium
answer_key: B
---

`cin >>` 在解析失败时流的状态变化容易被忽略。假设输入为 `abc`，以下代码输出是？

```cpp
#include <iostream>
int main() {
    int x = 100;
    std::cin >> x;
    std::cout << x << '\n';
    std::cin >> x;
    std::cout << x << '\n';
}
```

A. 100 和 0（第二个读取失败时赋 0）
B. 100 和 100（第二个读取直接失败，不改变 x）
C. 0 和 0（第一次读取就重置为 0）
D. 程序崩溃

---

**解析：**

`std::cin >> x` 读取整数时遇到 `abc`，解析失败，`failbit` 被置位。标准规定：**读取失败时不修改目标变量**（C++11 起，[istream.formatted.arithmetic]/3），所以 `x` 保留原值 100。

第二次 `std::cin >> x` 时，因为 `failbit` 仍然被设置（未调用 `clear()`），流拒绝任何输入操作，直接返回，`x` 再次不被修改，仍然输出 100。

**注意**：如果这是 C++03，`x` 会被赋为 0，但在 C++11+ 下保证不修改。这个 C++03→C++11 的变化是常见陷阱。