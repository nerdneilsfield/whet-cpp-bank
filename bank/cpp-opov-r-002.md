---
qid: cpp-opov-r-002
type: single
kp: [cpp-operator-overload]
difficulty: easy
answer_key: "C"
---

### 题目

阅读以下代码，`pre` 和 `post` 的值分别是什么？

```cpp
#include <iostream>

struct Counter {
    int val;
    Counter(int v) : val(v) {}

    Counter& operator++() {           // 前置 ++
        ++val;
        return *this;
    }

    Counter operator++(int) {         // 后置 ++
        Counter tmp = *this;
        ++val;
        return tmp;
    }
};

int main() {
    Counter c(10);
    Counter pre  = ++c;   // c.val 变为 11，pre 是引用返回值
    Counter post = c++;   // post 是旧值副本，c.val 变为 12
    std::cout << pre.val << " " << post.val << "\n";
}
```

A. `10 11`
B. `11 12`
C. `11 11`
D. `10 12`

## Explanation

`++c`（前置）先将 `c.val` 从 10 递增至 11，再返回 `*this` 的引用，故 `pre.val = 11`。`c++`（后置）先保存 `c` 的副本（`tmp.val = 11`），再递增 `c.val` 至 12，返回副本，故 `post.val = 11`。输出 `11 11`。
