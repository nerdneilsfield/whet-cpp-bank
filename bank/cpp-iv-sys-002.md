---
qid: cpp-iv-sys-002
type: short
kp: [cpp-interview]
difficulty: medium
tags: [华为, 阿里]
rubric:
  - 能按顺序说出四个阶段及其产物（.i / .s / .o / 可执行文件）
  - 预处理：宏展开、头文件展开、条件编译
  - 编译：语法/语义分析 → 中间代码 → 优化 → 目标汇编
  - 汇编：汇编代码 → 机器码目标文件（ELF .o）
  - 链接：符号解析、重定位、合并段，生成最终可执行文件
---

# 编译的四个阶段是什么？各产生什么文件？

## 参考答案

以 `gcc hello.c -o hello` 为例，完整流程分四个阶段：

### 阶段一：预处理（Preprocessing）

**命令**：`gcc -E hello.c -o hello.i`  
**产物**：`.i` 文件（展开后的纯 C 文本）

主要工作：
- 展开 `#include` — 将头文件内容原地插入
- 展开 `#define` 宏
- 处理 `#if / #ifdef / #ifndef / #endif` 条件编译
- 删除注释
- 处理 `#pragma`（留给后续阶段）

此阶段输出是**可读纯文本**，不含任何机器码。

### 阶段二：编译（Compilation）

**命令**：`gcc -S hello.i -o hello.s`  
**产物**：`.s` 文件（目标平台汇编代码）

主要工作：
1. **词法/语法分析** — 构建 AST
2. **语义分析** — 类型检查、作用域解析
3. **中间表示（IR）生成** — GCC 生成 GIMPLE/RTL，Clang 生成 LLVM IR
4. **优化** — 内联、常量折叠、死代码消除（受 `-O0`…`-O3` 控制）
5. **代码生成** — IR → 目标架构汇编

### 阶段三：汇编（Assembly）

**命令**：`gcc -c hello.s -o hello.o`（内部调用 `as`）  
**产物**：`.o` 目标文件（ELF 格式，含机器码）

汇编器将汇编指令逐条翻译为机器码，并生成：
- `.text` 节：代码
- `.data` / `.rodata` / `.bss` 节：全局数据
- **符号表（Symbol Table）**：记录本文件定义/引用的符号
- **重定位表（Relocation Table）**：外部符号占位，待链接器填写地址

### 阶段四：链接（Linking）

**命令**：`gcc hello.o -o hello`（内部调用 `ld`）  
**产物**：可执行文件（ELF executable）或共享库

主要工作：
- **符号解析（Symbol Resolution）** — 将所有 `.o` 文件的引用与定义匹配
- **重定位（Relocation）** — 填写真实虚拟地址，修正跳转/引用
- **段合并（Section Merging）** — 多个 `.text` 合并为一个
- 静态链接时一并合并 `.a` 库的目标文件；动态链接时在 ELF 中记录 `.so` 依赖，由运行时动态链接器（`ld-linux.so`）在加载时完成最终符号绑定

### 一图总结

```
hello.c
  ↓ 预处理 (cpp)    → hello.i   （宏展开文本）
  ↓ 编译   (cc1)    → hello.s   （汇编代码）
  ↓ 汇编   (as)     → hello.o   （ELF 目标文件）
  ↓ 链接   (ld)     → hello     （ELF 可执行文件）
```
