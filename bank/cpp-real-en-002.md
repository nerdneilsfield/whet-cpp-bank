---
qid: cpp-real-en-002
type: single
kp: [cpp-types, cpp-memory-mgmt]
primary_kp: cpp-types
difficulty: easy
answer_key: A
tags: [interview-real, interviewbit]
---
什么是 endianness（字节序）？以下说法正确的是？

A. 大端序（big-endian）将最高有效字节存储在最低地址；小端序（little-endian）将最低有效字节存储在最低地址
B. 小端序将最高有效字节存储在最低地址；大端序将最低有效字节存储在最低地址
C. endianness 只影响 `char` 类型的存储
D. 所有现代 x86 处理器都使用大端序

---

**解析：**

Endianness 指多字节数据在内存中的字节排列顺序：
- **大端序（big-endian）**：最高有效字节（MSB）存放在最低地址，符合人类的阅读习惯。
- **小端序（little-endian）**：最低有效字节（LSB）存放在最低地址，x86/x86-64 架构使用此方式。

嵌入式系统中不同架构（ARM 可配置、PowerPC 大端、x86 小端）混用时需要处理字节序转换。常用方法包括 `htons` / `ntohl` 等 POSIX 函数，或手动用移位运算转换。

**来源：** InterviewBit "C++ Interview Questions" — Endianness

## Explanation

正确答案是 A。
Endianness 指多字节数据在内存中的字节排列顺序： 大端序（big-endian）：最高有效字节（MSB）存放在最低地址，符合人类的阅读习惯。
小端序（little-endian）：最低有效字节（LSB）存放在最低地址，x86/x86-64 架构使用此方式。
嵌入式系统中不同架构（ARM 可配置、PowerPC 大端、x86 小端）混用时需要处理字节序转换。常用方法包括 htons / ntohl 等 POSIX 函数，或手动用移位运算转换。
