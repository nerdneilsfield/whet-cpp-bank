---
qid: cpp-taste-err-001
type: single
kp: [cpp-exceptions, cpp-memory-mgmt]
primary_kp: cpp-exceptions
difficulty: hard
answer_key: A
tags: [code-taste, best-practice]
---
某函数要打开一个文件、分配一段缓冲、调一个会抛异常的处理函数。四个版本功能相同，哪个品味最好？

```cpp
void process(const Buffer&);

// A
void run_a(const char* path) {
    std::ifstream in(path);
    std::vector<char> buf(4096);
    process(Buffer{in, buf});
}

// B
void run_b(const char* path) {
    FILE* fp = std::fopen(path, "r");
    char* buf = new char[4096];
    try {
        process(make_buffer(fp, buf));
    } catch (...) {
        delete[] buf;
        std::fclose(fp);
        throw;
    }
    delete[] buf;
    std::fclose(fp);
}

// C
void run_c(const char* path) {
    FILE* fp = std::fopen(path, "r");
    char* buf = new char[4096];
    if (!fp || !buf) goto cleanup;
    process(make_buffer(fp, buf));
cleanup:
    delete[] buf;
    if (fp) std::fclose(fp);
}

// D
void run_d(const char* path) {
    auto fp = std::shared_ptr<FILE>(std::fopen(path, "r"), std::fclose);
    auto buf = std::shared_ptr<char[]>(new char[4096], std::default_delete<char[]>());
    process(make_buffer(fp.get(), buf.get()));
}
```

A. A — 用 `std::ifstream` + `std::vector`，全部 RAII，函数体只有三行业务
B. B — 用原生资源 + try/catch/delete，显式表达异常路径的清理责任
C. C — 用 goto cleanup 集中错误处理，C 程序员熟悉的模式
D. D — 用 `shared_ptr` + 自定义 deleter 包装原生资源，也是 RAII

---

**解析：**

选 A。这道题考 **"RAII = 让构造-析构而不是 try/catch 负责清理"** 的核心品味。

A 三行代码：`ifstream` 析构关文件、`vector` 析构释放内存——**没有显式 try、没有显式 close、没有显式 delete**，函数体里只剩业务。如果 `process` 抛异常、抛出去的过程中栈展开，两个对象的析构按构造逆序自动调用，资源 100% 释放。这是 RAII 的范本。

逐一品味：

- **B**：技术上是对的——`try/catch(...)/throw` 是 RAII 之前 C++ 程序员处理异常清理的标准模板。但它有两个问题：(1) **代码膨胀**——业务一行被三段清理包围；(2) **重复**——成功路径 delete + close，异常路径也 delete + close，**写两遍等于以后改一处忘改一处**。任何"两套清理逻辑"都是 RAII 缺位的信号。
- **C**：`goto cleanup` 是 Linux 内核风格——内核不能用 C++ 异常、也不能用 RAII，goto 是它们的"最 RAII"。**但这是 C++ 代码**，把 C 内核的妥协当 C++ 品味是**搞错语言层级**。而且 C 写法里只能处理"提前 return"，对真正的异常（`process` 抛）完全不防御——`process` 抛了，控制流根本到不了 cleanup 标签，资源全泄漏。
- **D**：用 `shared_ptr<FILE>` 配 `fclose` deleter 包原生资源——属于"RAII 化老接口"的标准技巧，但 (1) **`shared_ptr` 是用于共享所有权的，单一所有权应该是 `unique_ptr`**；(2) 既然标准库已经有 `ifstream` 和 `vector`，**绕过它们去用原生 `FILE*` + `new char[]` 是反向选择**——好工具不用、再花力气把坏工具包装成好工具。`shared_ptr` 包 `FILE*` 是合理的，但**用在该用 `ifstream` 的地方**就是绕远路。

**核心识别点：**

- 看见 `try { ... } catch(...) { cleanup; throw; }` → 警觉，是不是该 RAII
- 看见 C++ 里用 `FILE*` / `new char[]` 而非 `ifstream` / `vector` → 警觉，标准库工具被绕过
- 看见 `goto cleanup` 在 C++ 代码里 → 警觉，C 风格污染
- 看见 `shared_ptr` 用于单一所有权 → 警觉，应该是 `unique_ptr`
- 函数体里"业务代码 vs 清理代码"比例 → 业务被埋没说明 RAII 缺位

A 的写法不是"少打了字"，而是**把"资源 = 对象"这个等式贯彻到底**——文件不是 `FILE*`，是 `ifstream`；缓冲不是 `char*`，是 `vector<char>`。每个资源都有一个负责它整个生命周期的对象，异常路径自动正确。Bjarne Stroustrup 设计 C++ 异常时说过的 "RAII is the most important technique for managing resources in C++"——这道题的 A 就是它的字面体现。

**来源：** 手写题。RAII 原理见 Bjarne Stroustrup *The C++ Programming Language* 4e §13.3；C++ Core Guidelines E.6, E.8, R.1；Linus Torvalds 在内核邮件列表上多次声明 goto cleanup 是 C 项目的"穷人 RAII"。

## Explanation

正确答案是 A。每个资源都有一个负责它整个生命周期的对象，异常路径自动正确。
这道题考 "RAII = 让构造-析构而不是 try/catch 负责清理" 的核心品味。
C：`goto cleanup` 是 Linux 内核风格——内核不能用 C++ 异常、也不能用 RAII，goto 是它们的"最 RAII"。
