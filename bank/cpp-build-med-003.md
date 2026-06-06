---
qid: cpp-build-med-003
type: single
kp: [cpp-build-tools]
difficulty: medium
answer_key: C
---

GCC/Clang 的 `-O2` 和 `-O3` 优化级别差异在于后者启用了更多"有风险"的优化。以下哪项是 `-O3` 相比 `-O2` **可能额外启用**的优化？

A. 函数内联（all functions inline）
B. 死代码消除（dead code elimination）
C. 循环向量化（loop vectorization）和函数重排（function reordering）
D. `-O3` 比 `-O2` 更快但生成的二进制总是更大

---

**解析：**

`-O3` 相比 `-O2` 的主要额外优化包括（GCC 文档）：

- `-fgcse-after-reload`：重载后的全局公共子表达式消除
- `-fipa-cp-clone`：过程间常量传播的克隆
- `-floop-interchange`、`-floop-unroll-and-jam`：循环变换和展开
- `-fpeel-loops`、`-fpredictive-commoning`：循环分裂和预测公共化
- `-fsplit-loops`、`-fsplit-paths`：循环/路径分裂
- `-ftree-loop-distribute-patterns`：循环模式分发
- **`-ftree-vectorize`**：循环自动向量化（利用 SIMD 指令）——这是 `-O3` 最重要的增量之一

A 错：函数内联在 `-O2` 和 `-O3` 都启用（`-finline-functions` 在 `-O2` 已启用）。

B 错：死代码消除在 `-O1` 开始就启用了。

D 错：`-O3` 不总是生成更大的二进制（有些优化缩短代码路径），但通常略微增大。

注意：`-O3` 在某些浮点计算中可能改变结果（因为向量化改变计算顺序），称为"优化 UB"。