---
qid: cpp-friend-r-001
type: single
kp: [cpp-friend]
difficulty: easy
answer_key: "B"
---

### 题目

阅读以下代码，程序输出是什么？

```cpp
#include <iostream>

class Box {
    int value = 42;
    friend void reveal(const Box& b);
};

void reveal(const Box& b) {
    std::cout << b.value << std::endl;
}

int main() {
    Box b;
    reveal(b);
}
```

A. 编译错误：`value` 是 private，`reveal` 无法访问
B. `42`
C. `0`
D. 未定义行为

## Explanation

正确答案是 B，输出 `42`。`reveal` 在 `Box` 内被声明为友元函数，因此虽然它不是成员函数，也能访问 `Box::value` 这个私有成员。A 项忽略了友元授权；C 项把默认成员初始化值误看成 0；D 项错误地认为私有访问会导致运行期未定义行为，实际访问权限是编译期规则。
