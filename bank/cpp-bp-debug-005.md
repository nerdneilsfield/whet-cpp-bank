---
qid: cpp-bp-debug-005
type: single
kp: [cpp-build-tools]
difficulty: medium
answer_key: C
---

启用 LTO（Link-Time Optimization）后，下列哪个**不是**LTO 的典型代价？

```bash
# 启用 LTO
g++ -O2 -flto -c a.cpp
g++ -O2 -flto -c b.cpp
g++ -O2 -flto a.o b.o -o app

# 全程序优化
clang++ -O2 -flto=thin   # ThinLTO，并行化
```

A. 链接时间显著增加（编译器要做跨 TU 优化和重新代码生成）
B. 内存占用增加（链接器需要加载所有 TU 的 IR）
C. 运行时性能下降
D. 增量构建变慢（修改一个文件触发重链接）

---

**解析：**

**LTO（Link-Time Optimization）** 把编译期分离的 TU IR 在链接时合并，进行跨 TU 优化：

- 跨 TU 内联（不再受 .cpp 边界限制）
- 跨 TU 死代码消除
- 全程序静态分析
- 更激进的去虚化（devirtualization）

**性能收益**：典型 5-20% 性能提升，二进制更小（可能减少 10-30%）。

**主要代价**：

| 维度 | 影响 |
|------|------|
| 链接时间 | **显著增加**（从秒级到分钟级），大型项目可慢 5-10 倍 |
| 内存占用 | 链接器要加载所有 TU 的 IR + 运行优化 pass，可能消耗 GB 级内存 |
| 增量构建 | **几乎被破坏**——改一个 .cpp 也要重链接整个二进制并重做 LTO |
| 调试 | 行号和符号信息可能错乱（行号映射在跨 TU 内联后不准确） |
| 编译器 bug 风险 | LTO 是复杂 pass 链，比传统优化更易触发编译器 bug |

**LTO 不会让运行时变慢**（除非编译器 bug）——它的目的就是优化运行时。所以 C 是错误描述。

工程实践：

**1. ThinLTO（Clang，GCC 9+）**：
- 把"全程序 LTO"切成"模块级 LTO + 链接时合并"
- 并行优化，链接时间可比传统 LTO 快 5-10 倍
- 增量构建友好
- 推荐用法：`-flto=thin`

**2. 选择性启用**：
```bash
# Release build
g++ -O3 -flto=thin -fuse-linker-plugin -o app *.cpp

# Debug build 不开 LTO
g++ -O0 -g -o app *.cpp
```

**3. CI 策略**：
- Debug build：不开 LTO（编译快）
- Release build：开 LTO（性能优）
- 性能测试：必须用 release+LTO 数据，否则数字不准

**4. PGO + LTO 组合**：
- 先 profile-guided 收集 hot path
- 再 LTO + PGO 全程序优化
- 收益再 +5-15%

正确答案 C。LTO 提升性能，不会让运行时变慢（D 描述的增量构建变慢确实是 LTO 的代价）。