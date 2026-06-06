---
qid: cpp-taste-err-007
type: single
kp: [cpp-exceptions]
primary_kp: cpp-exceptions
difficulty: hard
answer_key: A
tags: [code-taste, best-practice]
---
要同时获取两个资源（互斥锁 + 打开的文件句柄），中间 `process` 可能抛异常。四个版本功能相同，哪个品味最好？

```cpp
Obj process(std::unique_lock<std::mutex> lk, std::ifstream in);

// A
Obj run_a(const char* path) {
    static std::mutex mu;
    std::ifstream in(path);
    std::unique_lock lk(mu);
    return process(std::move(lk), std::move(in));
}

// B
Obj run_b(const char* path) {
    static std::mutex mu;
    std::ifstream in(path);
    if (!in.is_open()) throw std::runtime_error("open failed");
    mu.lock();
    try {
        Obj r = process(std::move(in));
        mu.unlock();
        return r;
    } catch (...) {
        mu.unlock();
        throw;
    }
}

// C
Obj run_c(const char* path) {
    static std::mutex mu;
    FILE* fp = std::fopen(path, "r");
    if (!fp) throw std::runtime_error("open failed");
    mu.lock();
    try {
        Obj r = process(fp);
        mu.unlock();
        std::fclose(fp);
        return r;
    } catch (...) {
        mu.unlock();
        std::fclose(fp);
        throw;
    }
}

// D
Obj run_d(const char* path) {
    static std::mutex mu;
    std::ifstream in(path);
    mu.lock();
    auto unlocker = at_scope_exit([&]{ mu.unlock(); });
    auto closer   = at_scope_exit([&]{ /* close ifstream dtors */ });
    return process(std::move(in));
}
```

A. A — `ifstream` RAII 管文件、`unique_lock` RAII 管锁，零手动释放
B. B — `try/catch/unlock` 管锁、ifstream 析构管文件
C. C — `try/catch/unlock + fclose`，全部手动
D. D — `scope_exit` 辅助函数，保证退出时调用清理

---

**解析：**

选 A。这道题考 **"RAII 的嵌套组合——多个资源的生命周期在异常下的配合"**。

A 只做了三件事：构造 `ifstream`（打开文件）、构造 `unique_lock`（加锁）、传进去处理。**如果 `process` 抛出异常，`lk` 的析构 unlock mutex、`in` 的析构 close 文件**——先后顺序由构造逆序自动保证。没有 try、没有 catch、没有手动 unlock、没有 scope_exit 辅助。这是 RAII 组合的标准模型：每个资源一个 RAII 包装，函数体只剩业务。

逐一品味：

- **B**：混合模型——`unique_lock` 能解决的事被手动 `lock/unlock` 做了。`try/catch/unlock` 还是"复制"了析构函数的逻辑。更糟的是：**`ifstream in(path);` 的文件关闭由析构负责，但 mutex 的 unlock 要手写**——两套风格不一致。"文件用 RAII、锁用手动"是**半吊子 RAII**，比全手动多了读者需要理解的认知切换。
- **C**：全手动。而且 `std::fopen` 返回的文件句柄要在 `process` 完成后 `fclose`——但 `process` 接受的是 `FILE*`，可能抛出也可能保留文件引用。这比 B 更退步：多了一堆手写 cleanup，`catch(...)` 写错一次就是泄漏。
- **D**：`scope_exit` 是 RAII 的替代包装——但模仿析构函数永远不如直接用析构函数。`scope_exit` 本身也要确保其 catch-all 拍子不带异常，而且 `closer = at_scope_exit([&]{ ... })` 实际上**没有在 closing `ifstream`**（`ifstream` 在其析构函数里自己关了），`closer` 在这里是冗余的。`scope_exit` 的真正价值在于"清理操作无法 RAII 化"的时候（比如某 C 库的 `free()`），对于标准库对象，已经有 RAII 就不需要它。

**核心识别点：**

- 多资源 + 可变动的异常路径 → RAII 嵌套 + 逆序析构
- 手动 `lock/unlock` + `try/catch` → 警觉 RAII 缺位的双路径清理
- `scope_exit` → 只在没有 RAII 包装的 C 资源上用
- C 资源（FILE* / malloc）和 C++ 资源混用 → 警觉风格不一致
- 检查在 RAII 构造前是否可能抛异常

A 的优雅来自一个简单的洞察：**任何资源一旦过了 RAII 构造那一步，它在任何后续的失败路径上都会自动释放**。构造顺序决定了释放逆序，这是 C++ 标准给的语言级别保证（stack unwinding）。Herb Sutter 在 *Exceptional C++* 里把"能 RAII 的都 RAII"称为 C++ 错误处理的第一原则：**永远不要让一个资源跨越 try/catch 边界。**

**来源：** 手写题。RAII 组合与逆序析构见 Herb Sutter *Exceptional C++* Items 9, 10, 11（全面讨论异常安全的三个级别）；ScopeExit 技术见 Andrei Alexandrescu *C++ Coding Standards* Item 22；RAII 是语言特性而非库特性见 Bjarne Stroustrup *The C++ Programming Language* 4e §13.3。

## Explanation

正确答案是 A。这道题考 "RAII 的嵌套组合——多个资源的生命周期在异常下的配合"。
这道题考 "RAII 的嵌套组合——多个资源的生命周期在异常下的配合"。
这比 B 更退步：多了一堆手写 cleanup，`catch(...)` 写错一次就是泄漏。
