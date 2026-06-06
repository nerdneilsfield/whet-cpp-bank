---
qid: cpp-build-med-002
type: single
kp: [cpp-build-tools]
difficulty: medium
answer_key: C
---

静态库的链接顺序在某些编译器中影响结果。假设有库 `libA.a`（依赖 `libB.a`）和 `libB.a`，以下哪种链接命令在 GCC/Clang 下**工作正常**？

A. `g++ main.o -lA -lB`
B. `g++ main.o -lA`（自动解析传递依赖）
C. `g++ main.o -lB -lA`
D. `g++ main.o -lA -lB` 和 `g++ main.o -lB -lA` 没有区别

---

**解析：**

GCC 和 Clang 的静态库链接器（`ld`）是单遍扫描（single-pass）：从左到右扫描命令行中的库，为每个未解析的符号寻找定义。如果符号在后面出现，前面已经扫描过的库就不会再被检查。

正确做法：**被依赖的库放在依赖者的后面**：

- `g++ main.o -lA -lB` ✅：扫描 `main.o` 发现未解析符号来自 A；扫描 `libA.a` 发现 A 依赖 B（符号未解析）；扫描 `libB.a` 解析这些符号。
- `g++ main.o -lB -lA` ❌：扫描 `libB.a` 时，没有未解析符号需要 B（main.o 不直接依赖 B）；扫描 `libA.a` 时发现依赖 B，但 `libB.a` 已经扫描过了，符号不能解析 → **链接失败**。

MSVC 的链接器默认是多遍扫描，没有这个问题。A 是正确的做法（A 依赖 B，所以 A 在 B 前面）。选项略作调整：A 正确顺序。

## 解析

正确答案为 C，因为“`g++ main.o -lB -lA`”符合题干所问的 C++ 规则或代码执行结果。A、B、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。构建题要区分预处理、编译、汇编、链接以及编译选项、库路径和目标文件的职责。
