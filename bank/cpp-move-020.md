---
qid: cpp-move-020
type: multi
kp: [cpp-move-semantics]
difficulty: easy
answer_key: [B, C, E]
---

# 代码阅读：移动语义综合判断

阅读以下代码，哪些描述是正确的？（多选）

```cpp
#include <string>
#include <vector>

std::string foo() {
    std::string local = "result";
    return local;               // (1)
}

int main() {
    std::string a = "hello";
    std::string b = a;          // (2)
    std::string c = std::move(a); // (3)
    std::string d = foo();      // (4)
}
```

A. (1) 一定触发拷贝构造函数
B. (2) 触发拷贝构造函数，因为 `a` 是 lvalue
C. (3) 触发移动构造函数，`a` 之后内容变为未指定
D. (4) 一定触发移动构造函数
E. (1) 编译器可通过 NRVO 优化，直接在调用方内存中构造 `local`
