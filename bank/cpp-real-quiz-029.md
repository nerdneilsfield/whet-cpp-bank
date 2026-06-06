---
qid: cpp-real-quiz-029
type: single
kp: [cpp-arrays-pointers]
primary_kp: cpp-arrays-pointers
difficulty: medium
answer_key: C
tags: [interview-real, cppquiz, language-lawyer]
---
根据 **ISO C++17** 标准（不考虑编译器扩展），以下程序的行为是？

```cpp
#include <iostream>
int main() {
    int n;
    std::cin >> n;
    int arr[n];          // (1) VLA?
    std::cout << sizeof(arr);
}
```

A. 合法（C99 起 VLA 是核心特性）
B. 输出 `sizeof(int) * n`
C. **不符合 ISO C++** 标准（VLA 非标准），仅作为 GCC 扩展存在
D. 行为未定义

---

**解析：**

[dcl.array]/1：C++ 数组的大小必须是 **constant expression**。`n` 在编译期未知，所以 `int arr[n]` **不是标准 C++**。

VLA（Variable-Length Array）是 **C99** 的核心特性，**C++ 标准从未接受**（C++14 曾尝试以 "arrays of runtime bound, ARB" 引入，被否决）。

GCC、Clang 默认提供 VLA 作为**扩展**，所以你写这段代码用 `g++ a.cpp` 可能编译过、运行正常输出 `4*n`。但用 `g++ -std=c++17 -pedantic` 会给警告，用 MSVC 直接编译错误：

```
error C2131: expression did not evaluate to a constant
```

正确的 C++ 写法：`std::vector<int> arr(n);`。

易混淆答案 A/B：在 GCC 默认模式下确实"能跑"，但**按标准**是不合法的——这是为什么严肃的跨平台项目要禁用 VLA。

**来源：** C++17 [dcl.array]/1；C++14 ARB 提案 N3810 被否