---
qid: cpp-bp-error-001
type: single
kp: [cpp-exceptions]
difficulty: medium
answer_key: C
---

考虑一个不可恢复的错误场景：配置文件校验失败，系统无法继续。以下哪种处理方式在工程上更合理？

```cpp
// 选项 A
void load_config(const std::string& path) {
    auto f = fopen(path.c_str(), "r");
    if (!f) throw std::runtime_error("config not found");
    // parse...
    fclose(f);
}

// 选项 B
void load_config(const std::string& path) {
    auto f = fopen(path.c_str(), "r");
    if (!f) {
        std::cerr << "FATAL: config not found\n";
        std::abort();
    }
    // parse...
    fclose(f);
}

// 选项 C
// 结合 fail-fast + 异常：快速崩溃在调试期，异常留给库用户
void load_config(const std::string& path) {
    auto f = fopen(path.c_str(), "r");
    if (!f) {
        if (std::getenv("DEBUG")) std::abort();
        throw std::runtime_error("config not found");
    }
    // parse...
    fclose(f);
}
```

A. 选项 A：纯异常，统一错误处理
B. 选项 B：abort 快速失败，简单直接
C. 选项 C：fail-fast in debug + exception in production 分层策略
D. 三种都可以，看心情

---

**解析：**

核心原则：**错误策略应与错误恢复可能性匹配。** 配置文件加载失败在调试阶段几乎总是开发者的笔误(typo)，abort 给出清晰的 core dump/call stack，比 catch 后静默恢复更能暴露问题。但相同错误到生产环境中，可能来自挂载卷未挂载等可纠正因素，抛出异常让上层恢复更合适。

选项 A 无差异处理，调试时开发者在异常链路中调试效率低。选项 B 一刀切 abort，生产环境中丧失恢复机会。选项 C 是典型的分层策略（fail-fast + 异常），也是 Google/Facebook 内部大量代码库采纳的模式。

正确做法：
```cpp
// 核心库函数抛出异常
// 入口处根据环境决定是否 abort
auto cfg = load_config("/etc/app.yaml");
if (!cfg) {
    if (is_debug_session()) std::abort();
    graceful_recovery();
}
```