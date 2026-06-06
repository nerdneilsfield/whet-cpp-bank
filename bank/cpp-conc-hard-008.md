---
qid: cpp-conc-hard-008
type: single
kp: [cpp-concurrency]
difficulty: medium
answer_key: B
---

以下场景描述了 **ABA 问题**：

```
初始状态：栈顶 A -> B -> C

线程1：读取栈顶 = A，准备执行 CAS(expected=A, desired=B)，将 A 弹出
线程1被挂起...

线程2：弹出 A，弹出 B，推入新节点 A'（地址与旧 A 相同，但内容不同）
栈变为：A' -> C

线程1恢复：CAS 检查栈顶仍为 A（地址相同），成功，将栈顶改为 B
但 B 已被释放！栈变为悬空指针状态。
```

解决 ABA 问题的**标准方法**是？

A. 改用 `compare_exchange_strong` 代替 `compare_exchange_weak`，强版本能检测到中间修改
B. 使用带版本号（标记指针）的 CAS：将指针与计数器打包为一个原子值，每次修改时递增计数器，即使地址相同版本号不同也会失败
C. 使用 `seq_cst` 内存序代替 `acquire/release`，全序保证能检测到中间的修改
D. 加互斥锁保护 CAS 操作，确保检查和交换之间不被打断

## 解析

正确答案是 B。release/acquire 配对用于发布数据和获取数据，建立 happens-before 关系。选项 B 的表述“使用带版本号（标记指针）的 CAS：将指针与计数器打包为一个原子值，每次修改时递增计数器，即使地址相同版本号不同也会失败”正好符合该规则。A、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
