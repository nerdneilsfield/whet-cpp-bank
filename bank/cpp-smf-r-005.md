---
qid: cpp-smf-r-005
type: single
kp: [cpp-special-members]
difficulty: easy
answer_key: "A"
---

## 题目

阅读以下代码，`copy(src)` 能否正常编译并运行？

```cpp
#include <iostream>

struct Resource {
    int* ptr;

    Resource() : ptr(new int(42)) { }

    // 用户定义了析构函数
    ~Resource() { delete ptr; }

    // 没有显式定义拷贝构造和拷贝赋值
};

Resource copy(Resource src) {
    return src;
}

int main() {
    Resource r;
    Resource r2 = copy(r);
    std::cout << *r2.ptr << "\n";
}
```

A. 能编译，输出 `42`，但存在双重释放的隐患（悬空指针）
B. 编译错误，用户定义析构后拷贝构造被删除
C. 能编译，编译器不再生成任何拷贝操作
D. 链接错误

## 解析

C++11 中，用户定义析构函数**不会阻止**编译器生成拷贝构造和拷贝赋值（但该行为在 C++11 中被标记为 deprecated）。因此代码可以编译运行，输出 `42`。然而编译器生成的是**浅拷贝**：`r` 和 `r2` 的 `ptr` 指向同一块内存，析构时会发生**双重 `delete`**，属于未定义行为。正确做法是遵循"三/五法则"：定义了析构，也要定义拷贝构造和拷贝赋值（或将其 `= delete`）。
