---
qid: cpp-real-quiz-025
type: single
kp: [cpp-undefined-behavior, cpp-io]
primary_kp: cpp-undefined-behavior
difficulty: hard
answer_key: D
tags: [interview-real, cppquiz, language-lawyer]
---
根据 C++17 标准，以下程序的行为是？

```cpp
#include <cstdio>
#include <cstddef>
int main() {
    std::size_t n = 42;
    std::printf("%d\n", n);
}
```

A. 保证输出 `42`
B. 编译错误
C. 输出 `0` 或乱码
D. 行为未定义

---

**解析：**

`printf` 是 C 风格变参函数（va_args）。`%d` 要求对应 `int` 类型实参；而 `std::size_t` 在大多数 64 位平台是 `unsigned long` 或 `unsigned long long`，**类型不匹配**。

按 C 标准（C++ 引用之）`7.21.6.1`：转换说明符与对应实参类型不匹配是**未定义行为**。在 64-bit little-endian 上，常常恰好只读了低 32 位，"看起来"输出 42；但只要 size_t 高 32 位非零（更大数字），输出就是错的。

正确写法：
- `%zu` 对应 `size_t`
- `%lu` 对应 `unsigned long`
- 用 `std::cout`：`std::cout << n;`（C++ I/O 是类型安全的）

编译器（GCC `-Wformat`）通常给警告，但不是编译错误，不阻止运行。

**来源：** C11 §7.21.6.1（C++ 通过 [c.printf] 引入）

## Explanation

正确答案是 D。
printf 是 C 风格变参函数（va_args）；%d 要求对应 int 类型实参；而 std::size_t 在大多数 64 位平台是 unsigned long 或 unsigned long long，类型不匹配。
按 C 标准（C++ 引用之）7.21.6.1：转换说明符与对应实参类型不匹配是未定义行为；在 64-bit little-endian 上，常常恰好只读了低 32 位，"看起来"输出 42；但只要 size_t 高 32 位非零（更大数字），输出就是错的。
正确写法： %zu 对应 size_t %lu 对应 unsigned long 用 std::cout：std::cout << n;（C++ I/O 是类型安全的） 编译器（GCC -Wformat）通常给警告，但不是编译错误，不阻止运行。
