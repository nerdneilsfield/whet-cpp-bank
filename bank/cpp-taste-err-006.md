---
qid: cpp-taste-err-006
type: single
kp: [cpp-exceptions, cpp-stl-basics]
primary_kp: cpp-exceptions
difficulty: hard
answer_key: C
tags: [code-taste, best-practice]
---
要从一个配置文件中读取数据，文件可能不存在、格式可能错误。四个版本功能相同，哪个品味最好？

```cpp
class Config { /*...*/ };

// A
Config load_a(const char* path) {
    std::ifstream f(path);
    if (!f.is_open()) throw std::runtime_error("file not found");
    Config c;
    if (!(f >> c)) throw std::runtime_error("parse failed");
    return c;
}

// B
Config load_b(const char* path) {
    std::ifstream f(path);
    assert(f.is_open() && "config file must exist");
    Config c;
    bool ok = static_cast<bool>(f >> c);
    assert(ok && "config file must be valid");
    return c;
}

// C
std::expected<Config, std::error_code> load_c(const char* path) {
    std::ifstream f(path);
    if (!f.is_open()) return std::unexpected(
        std::make_error_code(std::errc::no_such_file_or_directory));
    Config c;
    if (!(f >> c)) return std::unexpected(
        std::make_error_code(std::errc::bad_message));
    return c;
}

// D
bool load_d(const char* path, Config& c) {
    std::ifstream f(path);
    if (!f.is_open()) return false;
    if (!(f >> c)) return false;
    return true;
}
```

A. A — 文件或格式错误就抛异常，最简单
B. B — 用 `assert` 把配置加载假设为"必须存在"，开发阶段快速暴露
C. C — `expected<Config, error_code>` 类型安全地承载成功或失败原因
D. D — `bool + 出参` 最传统，调用方可以当场处理

---

**解析：**

选 C。这道题考 **"文件加载是一种通用失败来源、失败原因需要区分 + 非异常路径处理"**。

配置文件加载的两个失败场景——**文件不存在**和**格式错误**——对应不同的恢复策略：文件不存在可能 fallback 到默认配置、格式错误可能需要报错退出。用 `expected`（C++23）或它的实验版 predecessors（tl::expected, Boost.Outcome）把**所有可能的失败编码在返回类型**里，调用方用 pattern matching 或 `.or_else()` 分别处理。

逐一品味：

- **A**：抛异常在这次的场景里**不是最坏选择**（至少失败原因带上了），但它有两层问题：(1) 加载配置作为"程序启动时发生的"过程，异常意味着 `try { auto c = load_a(...); } catch(...) { /* 怎么办？ */ }`——在很多 main 函数的上下文中用户不处理就是 `terminate`，(2) 异常路径在热分离路径上损失了"哪个失败场景"的区分——如果用 `expected`，调用方可以优雅地 `auto c = load_c(...).value_or(default_config)`，一行解决。
- **B**：**致命错误——`assert` 在 Release 宏不启用编译**。所有 `assert` 消失后，加载失败没有任何路径检查、访问 `c` 是未定义行为。把"运行时经常发生的失败"用只 Debug 有效的 assert 处理，等于说"线上是赌场"。
- **D**：`bool + 出参` 和 err-003 的批评相同——bool 无法编码失败原因，"加载失败"被简化成了明/暗，调用方得不到任何关于"为什么失败"的线索。如果把错误原因放到另一个出参里，就要 `bool load(..., std::error_code& ec)`——开始向 `expected` 方向演化但不完全，还要多写一个参数。

**核心识别点：**

- 文件加载有多种失败（not found / permission / format）→ `expected` 带 error_code
- `assert` 验证文件是否存在 → 警觉 Release 失效，应该在 if 之后处理
- 文件不存在是"期望的失败"→ 不抛异常 + 给错误原因
- 看见 `bool f(T& out)` 并行的 `is_open` 隐式转为 bool → 警觉失败原因丢失

C 用 `expected<Config, error_code>` 是 P0323 提案的代表用例。注意区分：errc（可移植的错误代码枚举）和 errno（平台相关）的不同。用 `make_error_code(errc::no_such_file_or_directory)` 生成了可移植的 error_code，而不是手写字符串。

**来源：** 手写题。`expected` 与文件 I/O 用例见 C++ Core Guidelines E.2, E.16; `std::error_code` 设计见 Christopher Kohlhoff (ASIO 作者) 的设计文档; P0323 `std::expected` 提案 (Vicente Botet et al.)。

## Explanation

正确答案是 C。这道题考 "文件加载是一种通用失败来源、失败原因需要区分 + 非异常路径处理"。
这道题考 "文件加载是一种通用失败来源、失败原因需要区分 + 非异常路径处理"。
配置文件加载的两个失败场景——文件不存在和格式错误——对应不同的恢复策略：文件不存在可能 fallback 到默认配置、格式错误可能需要报错退出。
