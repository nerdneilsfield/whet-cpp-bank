---
qid: cpp-func-r-002
type: single
kp: [cpp-functions]
difficulty: easy
answer_key: C
---

# 代码阅读：重载解析歧义

以下代码能否编译通过？

```cpp
#include <iostream>
void print(int x)  { std::cout << "int"; }
void print(long x) { std::cout << "long"; }

int main() {
    print(42);   // 42 是 int 字面量，没有问题
    print(42L);  // 42L 是 long 字面量，没有问题
    print('A');  // char 可隐式转换为 int 或 long，两个重载同样匹配
    return 0;
}
```

A. 编译通过，输出 `intlongint`
B. 编译通过，输出 `intlonglong`
C. 编译失败，`print('A')` 调用产生歧义，无法确定最佳重载
D. 运行时未定义行为
