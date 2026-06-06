---
qid: cpp-real-en-028
type: single
kp: [cpp-functions, cpp-preprocessor]
primary_kp: cpp-functions
difficulty: medium
answer_key: C
tags: [interview-real, roadmap-sh]
---
在 C++ 中使用 `inline` 函数的优势和限制是什么？

A. `inline` 关键字保证函数一定会被内联展开，没有限制
B. `inline` 只在调试模式下有效，发布模式下自动生效
C. `inline` 是编译器的建议而非强制，优势是避免函数调用开销（适合短小函数），限制是体积膨胀和滥用可能导致指令缓存压力增大
D. `inline` 函数不能有参数

---

**解析：**

`inline` 关键字向编译器建议将函数调用替换为函数体直接展开，从而消除函数调用栈帧开销。

**优势**：
- 消除函数调用开销（参数压栈/出栈、跳转）
- 配合编译时的上下文优化（如常量传播）
- 适合小而频繁调用的函数（如 getter / setter）

**限制/注意事项**：
- **只是建议**：编译器可以忽略 `inline`（如递归函数、过长函数不会内联）
- **代码膨胀**：多处调用时每处都展开，可执行文件体积增大
- **指令缓存压力**：大量内联可能导致指令缓存命中率下降
- 现代编译器在优化级别（如 `-O2` / `-O3`）下会自动内联，`inline` 更多用于 ODR（单定义规则）豁免（允许在头文件中定义函数）
- 内联函数的定义必须在调用处可见（通常放在头文件）

**来源：** roadmap.sh "C++ inline functions"