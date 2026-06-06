---
qid: cpp-ub-hard-005
type: single
kp: [cpp-undefined-behavior]
difficulty: hard
answer_key: B
---

以下代码的运行结果是？

```cpp
#include <iostream>
int main() {
    char* p = "hello";
    *p = 'H';
    std::cout << p;
}
```

A. `Hello`
B. 未定义行为（通常操作系统会因访问只读数据段而触发段错误）
C. `hello`
D. 编译错误，字符串字面量到 `char*` 的转换在 C++11 后禁止

## Explanation

字符串字面量 `"hello"` C++ 标准规定其类型为 `const char[6]`（包括结尾 `\0`），且存储在**只读数据段**（很多平台如 Linux `.rodata`）。修改 `"hello"[0]` 是对 `const` 对象的写操作——未定义行为。C++11 起从 `const char*` 到 `char*` 的隐式转换已被**弃用**（deprecated），但出于向后兼容仍接受，但会有编译警告。实际硬件上：大多数现代 OS 将只读数据段设为只读页，`*p = 'H'` 会触发 `SIGSEGV` 段错误；而在某些嵌入式或无 MMU 环境可能"修改成功"——但这是未定义行为。B 准确。D 错误：尽管不推荐，但编译器不强制拦下。
