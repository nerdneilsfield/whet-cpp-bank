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

## Explanation

正确答案是 B、C、E。`b = a` 中 `a` 是左值，所以拷贝；`std::move(a)` 让 (3) 调用移动构造，之后 `a` 有效但内容未指定；`return local` 可做 NRVO。A 和 D 都错在说“一定”：返回值优化可能消除拷贝/移动，不能固定为某一种调用。
