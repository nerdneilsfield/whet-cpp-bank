---
qid: cpp-bp-multi-med-004
type: multi
kp: [cpp-build-tools]
difficulty: medium
answer_key: [A, B, C]
---
关于编译器警告与 sanitizer 工具，**哪些说法是正确的**？（多选）

A. `-Wall -Wextra` 是编译期静态检查，能在不运行程序的情况下发现未使用变量、未初始化、类型比较等问题
B. AddressSanitizer (`-fsanitize=address`) 在**运行期**检测堆/栈缓冲区溢出、use-after-free、double-free 等内存错误，性能开销约 2× 但不能检测数据竞争
C. ThreadSanitizer (`-fsanitize=thread`) 在运行期检测数据竞争，但与 ASan 互斥（不能同时启用）
D. UndefinedBehaviorSanitizer (`-fsanitize=undefined`) 能在编译期发现所有未定义行为，无需运行测试

---

**解析：**

A 正确：`-Wall -Wextra` 是 GCC/Clang 的静态警告组合，覆盖未使用、可疑比较、缺失初始化等常见问题。建议工程中再加 `-Wpedantic -Wshadow -Wconversion`。
B 正确：ASan 是动态运行时工具，捕获各类内存安全错误。开销约 2× 内存、2× 时间。不检测线程竞争（那是 TSan 的工作）。
C 正确：TSan 用影子内存追踪 happens-before 关系来检测竞争；与 ASan 实现机制冲突（影子内存布局不同），编译期就互斥。一般做法：CI 跑两个独立 job。
D 错误：UBSan 是**运行期**检测器，触发的 UB 必须实际执行到才会捕获；它无法发现未走到的死代码中的 UB。也不能保证发现所有 UB——只能发现已实现检测器的一类（如有符号溢出、空指针解引用、对齐违规等）。