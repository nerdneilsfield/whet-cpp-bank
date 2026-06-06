---
qid: cpp-iv-sys-001
type: short
kp: [cpp-interview]
difficulty: medium
tags: [字节跳动, 华为]
rubric:
  - 说明可变参数原理：参数压栈顺序（右→左）、调用约定
  - 能描述 va_list/va_start/va_arg/va_end 四个宏的作用
  - 知道格式字符串解析驱动参数读取，类型安全靠调用者保证
  - 提到 printf 最终调用系统调用 write(1, buf, n)
  - 加分：提到 vprintf/vsnprintf 族，以及 __attribute__((format)) 的编译器检查
---

# `printf` 是如何实现的？（可变参数机制）

## 参考答案

### 1. 可变参数的底层原理

C 语言的可变参数依赖**调用约定（calling convention）**。在 x86-64 System V ABI 中，整数/指针参数前 6 个走寄存器（rdi、rsi、rdx、rcx、r8、r9），超出部分及浮点参数按规则放入栈帧。`printf` 的第一个参数（格式字符串）在 `rdi`，其余可变参数依次排布，`va_list` 本质上是一个指向这片参数区域的游标。

### 2. va_list / va_start / va_arg / va_end

```c
#include <stdarg.h>

int my_printf(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);   // 初始化 ap，指向 fmt 之后的第一个参数
    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
            if (*fmt == 'd') {
                int v = va_arg(ap, int);   // 按 int 取出，游标后移
                // 把 v 转为字符串写入输出缓冲区
            } else if (*fmt == 's') {
                char *s = va_arg(ap, char *);
                // 写入字符串
            }
            // ... 其他格式符
        } else {
            // 普通字符直接输出
        }
        fmt++;
    }
    va_end(ap);          // 清理（某些平台释放寄存器保存区）
    return /* 已输出字符数 */;
}
```

- `va_start(ap, last)` — 让 `ap` 指向 `last` 参数之后的位置。
- `va_arg(ap, type)` — 从 `ap` 当前位置读取 `type` 大小的值并推进游标。类型不匹配是 **未定义行为（UB）**，运行时无法检测。
- `va_end(ap)` — 在某些 ABI（如 ARM AAPCS）上需要清理栈或寄存器转储区，x86-64 通常是 no-op，但必须调用以保证可移植性。

### 3. 格式字符串解析 → 系统调用

`printf` 将格式化结果写入一个内部缓冲区（通常通过 `FILE *stdout`），最终调用：

```c
write(STDOUT_FILENO, buf, len);  // Linux 系统调用 syscall(SYS_write, 1, buf, len)
```

glibc 实现中，`printf` → `vfprintf` → `_IO_vfprintf_internal`，复杂度主要在格式符解析和数字/浮点转字符串的逻辑上。

### 4. 类型安全

可变参数**没有运行时类型信息**，安全性完全依赖调用者使格式串与参数类型匹配。GCC/Clang 提供 `__attribute__((format(printf, 1, 2)))` 在编译期静态检查，这也是为什么现代 C++ 更倾向 `std::format`（C++20）——它通过模板在编译期捕获类型不匹配。
