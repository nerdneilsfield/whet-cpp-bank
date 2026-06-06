---
qid: cpp-scope-r-003
type: single
kp: [cpp-scope-linkage]
difficulty: easy
answer_key: C
---

### 题目

项目有两个源文件。`a.cpp` 定义了一个 `static` 函数，`b.cpp` 试图声明并调用它。链接结果是什么？

```cpp
// a.cpp
#include <iostream>
static void greet() {
    std::cout << "hello\n";
}

// b.cpp
void greet();   // 声明
int main() {
    greet();    // 调用
}
```

A. 输出 `hello`
B. 编译错误：`greet` 未声明
C. 链接错误：`greet` 未定义
D. 运行时崩溃

## Explanation

C


`static` 修饰的全局函数具有**内部链接（internal linkage）**，其可见性仅限于定义它的翻译单元（`a.cpp`）。`b.cpp` 中的声明虽然能通过编译，但链接器在 `b.cpp` 的符号表中找不到 `greet` 的定义，从而产生链接错误（`undefined reference to 'greet'`）。
