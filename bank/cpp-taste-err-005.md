---
qid: cpp-taste-err-005
type: single
kp: [cpp-exceptions, cpp-classes]
primary_kp: cpp-classes
difficulty: hard
answer_key: B
tags: [code-taste, best-practice]
---
某个 `Database` 类的析构函数里关闭底层连接，关闭时检测到数据尚未 flush。四个版本作者的选择不同，哪个品味最好？

```cpp
class Database {
    DBHandle h_;
public:
    ~Database() {
        // A
        if (!flush(h_)) { /* 忽略 */ }

        // B
        if (!flush(h_)) {
            try { log("flush failed in dtor"); }
            catch (...) {}
        }

        // C
        if (!flush(h_)) {
            std::abort();
        }

        // D
        if (!flush(h_)) {
            throw std::runtime_error("flush failed");
        }
    }
};
```

A. A — 忽略，析构函数里 ITBS（"It's The Business, Stupid"）
B. B — 记录日志，但要保证 catch 一切防止日志本身抛
C. C — `std::abort`，无法恢复的核心错误就该死
D. D — 抛异常，让调用方的栈展开时能知道连接出了问题

---

**解析：**

选 B。这道题考 **"析构函数里检测到错误的黄金法则：不抛、不忽略、记录日志是最底线"**。

析构函数在栈展开期间（stack unwinding）被调用时，**如果抛第二个异常，调用 `std::terminate()`**。即使不在 unwind 期间，抛异常的析构函数也违反 C++ 核心准则——因为对象生命周期已到，没有任何外部代码能 catch 掉这个"从析构函数逃逸的异常"来清理残留状态。所以两个极端都是错的：忽略（A）和抛异常（D）。折中方案是 B：**检测到错误、记录日志（让运维能发现）、然后默默忍受**。

逐一品味：

- **A**：完全沉默。在析构函数后来看逐行日志发现"昨天 flush 了但没关闭"，没有任何线索留下。**不可侦查的错误是最差实践**——等于把问题埋到下次故障排查时。析构函数里的错误可以不做激进处理，但至少留下一条日志。
- **C**：`abort` 可能正确——如果 **flush 失败意味着数据库状态已经不一致、继续运行只会制造更大的破坏**（比如金融交易）。但数据库 flush 失败通常是"网络断了一下重连就能恢复"，不是"程序应该死"的级别。`abort` 是最极端的选择，只应留给那些不 abort 就丢掉数据完整性担保的场景。**默认选 abort 是 overreaction**。
- **D**：**致命错误**。析构函数如果因为抛出异常而脱离了当前 `~Database()` 的栈帧（无论是直接抛还是在 unwind 中二次抛），要么形成 double-exception → `terminate`，要么对象的部分成员析构被跳过（未定义行为）。C++ 标准 15.2/2:"If a destructor exits via an exception, ... destructors for objects whose lifetime has ended will be invoked ... and the destructor should not throw"。**不在析构函数里抛是一条死规矩**。

**核心识别点：**

- 析构函数发现错误 → 记录日志（若有可能），不抛异常
- 看见析构抛异常 → 警觉 UB / `terminate`
- 看见析构完全忽略 → 警觉不可侦查错误
- 看见析构 `abort` → 检查是不是真的不可恢复
- Catch 日志的异常 → 确保日志抛异常不会二次崩溃

B 的写法也展示了 self-defensive："日志 API 本身也可能抛异常（比如磁盘满）怎么办？"——外层 catch(...) 吞掉它，宁可日志丢了也不让日志抛导致 terminate。**这种"连日志的异常都防住了"的写法才是真正理解了析构函数异常安全的边界**。

**来源：** 手写题。"Destructors that throw or you die" 见 Herb Sutter *Exceptional C++* Item 13；ISO/IEC 14882:2017 §15.2/2；C++ Core Guidelines E.16, C.40；Scott Meyers *Effective C++* 3e Item 8 "Prevent exceptions from leaving destructors"。

## Explanation

正确答案是 B。C：`abort` 可能正确——如果 flush 失败意味着数据库状态已经不一致、继续运行只会制造更大的破坏（比如金融交易）。
析构函数在栈展开期间（stack unwinding）被调用时，如果抛第二个异常，调用 `std::terminate()`。
这道题考 "析构函数里检测到错误的黄金法则：不抛、不忽略、记录日志是最底线"。
