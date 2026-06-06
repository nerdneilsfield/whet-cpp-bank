---
qid: cpp-bp-modern-004
type: single
kp: [cpp-cpp14-17]
difficulty: medium
answer_key: D
---

C++20 引入了 `[[likely]]` 和 `[[unlikely]]` 属性（CPP 属性）。以下哪个属于**正确且有意义的使用**？

```cpp
// A
void process(int code) {
    switch (code) {
        [[unlikely]] case 0: abort();
        [[likely]]   case 1: do_normal();
        default: handle_rest();
    }
}

// B
if (buf.size() > expected)
    [[unlikely]] { grow(); }

// C
[[likely]] constexpr bool is_even(int n) { return n % 2 == 0; }

// D
while (true) {
    auto buf = read_chunk();
    if (!buf) [[unlikely]] break;   // 通常成功，失败极少
    process(buf);
}
```

A. A
B. B
C. C
D. D

---

**解析：**

`[[likely]]` / `[[unlikely]]` 允许程序员表达分支的预期执行频率，帮助编译器优化：

- **代码排列优化**：likely 的分支连续排列在 hot 区，unlikely 分支移到 cold 区（甚至 .text.cold 段），改善 icache 局部性
- **分支预测提示**：部分架构可以调流水线（x86 的 `__builtin_expect` 包装）

**标准用法**（CWG 2249 明确了只能用在语句或标号前）：

```cpp
// 正确用法
if (...) [[likely]] { ... }
if (...) [[unlikely]] { ... }
switch (x) { case 1: [[likely]] ...; break; }

// 错误用法
[[likely]] if (...) { ... }    // 格式不对，属性必须用 syntax-correct 位置
```

- **A**：正确格式，但调用 `[[likely]]` / `[[unlikely]]` 在 switch case 中是 C++23 才正式允许的（CWG 2561），C++20 仅允许 if/else
- **B**：语法错误（属性不能放在 `{` 前面）
- **C**：没有分支——constexpr 函数在编译期执行，运行时不存在硬件分支
- **D：正确**。IO 循环中成功读入是常见情况（likely），`!buf`（EOF/错误）是特殊情况（unlikely）

工程建议：
1. 不要到处加 `[[likely]]`/`[[unlikely]]`——只有在**性能实测证明**某个分支确实比另一个显著更常见时，而且编译器生成的代码排列证明有差距，才值得加
2. 错误位置上的 attribute 被编译器忽略（不报错！）——程序员看不到 warning 就以为生效了
3. `[[likely]]` 在 if/else 中的具体位置是**条件体前面**：

```cpp
if (is_error) [[unlikely]] {
    handle_error();   // 编译器把这个块放 .cold
} else [[likely]] {
    process();        // 随便主路径
}
```

正确答案 D。