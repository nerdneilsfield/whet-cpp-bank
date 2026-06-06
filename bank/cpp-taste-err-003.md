---
qid: cpp-taste-err-003
type: single
kp: [cpp-exceptions]
primary_kp: cpp-exceptions
difficulty: hard
answer_key: B
tags: [code-taste, best-practice]
---
要写一个"按 key 查找配置值"的函数：查得到返回值，查不到要让调用方知道。四个版本功能相同（都能让调用方区分成功与失败），哪个品味最好？

```cpp
class Config { /*...*/ };

// A
std::string find_a(const Config& c, const std::string& key);
// 找不到时抛 std::out_of_range

// B
std::optional<std::string> find_b(const Config& c, const std::string& key);
// 找不到时返回 std::nullopt

// C
std::expected<std::string, std::string> find_c(const Config& c, const std::string& key);
// 找不到时返回 std::unexpected("key not found: ..." )

// D
bool find_d(const Config& c, const std::string& key, std::string& out);
// 找不到返回 false、out 不修改
```

A. A — 抛异常最简洁，调用方按需 try/catch
B. B — `std::optional` 把"可能没有"编码在类型里，零异常开销、调用方必须显式处理
C. C — `std::expected`（C++23）能带错误信息，比 optional 表达力强
D. D — 用 `bool` + 出参，C 风格，最高效

---

**解析：**

选 B。这道题考 **"key 查不到是预期的、不是异常"这一关键判断**——结合 optional/expected/异常的适用场景。

"配置里没这个 key"是**正常业务流的一部分**——调用方完全可能会查不到、然后用默认值、或走另一条路径。这是**预期分支**，不是异常情况。异常的语义是"**不应该发生的、当前层无法处理的、必须改变控制流让上层处理**"的事件。把"查不到"做成抛异常是**性能（异常路径慢一到两个数量级）和语义（误导上层这是错误）的双重错配**。

逐一品味：

- **A**：常用的"标准容器风格"——`std::map::at` 找不到抛 `out_of_range`。但**`at` 是当 key 一定该存在的"防御性 API"**，而我们这里写的是"查询 API"。Herb Sutter 在 P0709（Zero-overhead deterministic exceptions 提案）里反复强调："Use exceptions for errors that are caused by conditions you don't normally expect"。配置 key 缺失不属于此。
- **C**：`std::expected<T, E>`（C++23）是 optional 的"带错误原因"版本——查不到能告诉调用方为什么。**但这里的"为什么"只有一种**（key 不存在），错误信息和调用方传进来的 key 一一对应，**没有信息增量**。`expected` 的真正用武之地是"失败原因有多种、调用方需要根据原因区分处理"（如 IO 失败：file-not-found vs permission-denied vs disk-full）。**单一失败原因 → optional 就够，多种失败原因 → expected**。
- **D**：`bool + 出参` 是 C 风格遗留——(1) 强迫调用方先声明一个空 `string` 才能调用，无法链式；(2) 失败时 `out` 状态不明（这里写"不修改"，但 review 时要查文档/源码才能确认）；(3) 不能用于 `const` 上下文、不能赋值到 `auto x = ...`、不能放进表达式。**类型系统拒绝表达"成功才有值"这件事**是 C 时代的妥协，C++17 后有 optional 就别再走这条路。

**核心识别点：**

- 失败是预期分支 + 单一失败原因 → `std::optional`
- 失败是预期分支 + 多种失败原因 → `std::expected`（C++23）
- 失败是真异常（违反前置条件、IO 设备坏、内存不够）→ 抛异常
- 看见 `bool foo(..., T& out)` → 警觉，类型系统没表达成功语义
- 看见"找不到就抛 `out_of_range`" → 警觉，是不是把预期当异常

P0709 / Herb Sutter 的总结很经典：**"errors that are not exceptional should not use exceptions"**。`optional` 让"可能没有"成为类型契约的一部分——调用方无法忘记处理，编译器替你强制 `.has_value()` 或解构。

**来源：** 手写题。`optional` 设计动机见 N3793 (Fernandes & Zarzycki) "A proposal to add a utility class to represent optional objects"；`expected` 见 P0323；Herb Sutter "Zero-overhead deterministic exceptions: Throwing values" (P0709)；C++ Core Guidelines E.2, E.3, E.16。

## Explanation

正确答案是 B。这道题考 "key 查不到是预期的、不是异常"这一关键判断——结合 optional/expected/异常的适用场景。
这道题考 "key 查不到是预期的、不是异常"这一关键判断——结合 optional/expected/异常的适用场景。
这是预期分支，不是异常情况。
