---
qid: cpp-bp-init-004
type: single
kp: [cpp-classes]
difficulty: medium
answer_key: A
---

以下代码在多文件链接时可能出现什么灾难性结果？

```cpp
// logger.h
struct Logger {
    static std::unordered_map<std::string, int> counters;  // 声明
    static void inc(const std::string& k) { counters[k]++; }
};

// logger.cpp
#include "logger.h"
std::unordered_map<std::string, int> Logger::counters;    // 定义

// main.cpp
#include "logger.h"
int main() {
    Logger::inc("hello");
}
```

假设有人不小心在 `logger2.cpp` 中也写了 `std::unordered_map<std::string, int> Logger::counters;`，会怎样？

A. 链接失败（duplicate symbol），幸无运行时损失
B. 运行时出现两个全局 map，一个 inc 的数据不在另一个里
C. 两个定义合并成一个，正常工作
D. 编译都能通过但运行时崩溃

---

**解析：**

静态成员变量的定义（非 inline）遵循**单一定义规则（ODR）**。同一个符号在多个 .cpp 文件中定义 = **多重定义**，链接器报 `duplicate symbol` 错误（除非符号被 weak 修饰）。

但这里只是"假设"，实际更常见的工程问题是：

1. **头文件中定义 static 成员**（不加 `inline` 或者忘了在 .cpp 中定义）：每个包含头文件的 TU 都有副本 → 链接错误
2. **C++17 起 `inline` 修复了这个问题**：

```cpp
// logger.h — C++17
struct Logger {
    inline static std::unordered_map<std::string, int> counters;  // inline 定义
};
```

`inline static` 成员变量在 C++17 起允许直接在类内定义，**不会产生多重定义冲突**（多个 TU 的 inline 定义会被链接器合并为单一对象）。这是 C++17 最重要的简化之一。

正确做法：
- C++17 后：用 `inline static` 替代类外定义
- C++14 及以前：必须且只能在一个 .cpp 中定义

补充：**static init fiasco**（静态初始化顺序问题）—— `Logger::counters` 如果被其他静态对象在其之前访问，会 UB。工程上：
- 避免非 trivial 静态全局变量
- 用 `constexpr` 解决元间常量
- 用 local static（C++11 线程安全初始化）+ 引用包装