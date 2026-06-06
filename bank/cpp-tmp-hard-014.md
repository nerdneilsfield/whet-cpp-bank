---
qid: cpp-tmp-hard-014
type: single
kp: [cpp-templates]
difficulty: hard
answer_key: A
---

比较 Policy 模板参数与虚函数策略的运行时开销：

```cpp
// 方式 A：Policy-Based（编译期）
template<typename LogPolicy>
class Engine {
public:
    void run() { LogPolicy::log("running"); }
};

struct FileLog {
    static void log(const char* msg) { /* 写文件 */ }
};

Engine<FileLog> e;
e.run();  // 直接调用 FileLog::log，无间接跳转

// 方式 B：虚函数策略（运行时）
struct ILog { virtual void log(const char* msg) = 0; };
struct FileLog2 : ILog {
    void log(const char* msg) override { /* 写文件 */ }
};

class Engine2 {
    ILog* logger_;
public:
    Engine2(ILog* l) : logger_(l) {}
    void run() { logger_->log("running"); }  // 虚函数分派
};
```

关于两种方式的性能，以下说法正确的是？

A. 方式 A 在编译期解析调用目标，可内联优化，无虚函数分派开销；方式 B 每次调用需经过虚表查找
B. 方式 B 比方式 A 更快，因为虚函数表是连续内存，缓存命中率更高
C. 两者性能完全一致，现代编译器会对虚函数调用做去虚化优化
D. 方式 A 因模板实例化膨胀，实际上比方式 B 更慢

## Explanation

正确答案是 A，即 方式 A 在编译期解析调用目标，可内联优化，无虚函数分派开销；方式 B 每次调用需经过虚表查找。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 B、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。模板题要区分编译期实例化、类型推导、特化/重载匹配和 SFINAE/约束；不要把模板当作运行时多态。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
