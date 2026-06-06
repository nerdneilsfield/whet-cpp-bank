---
qid: cpp-prog-mem-fd-001
type: prog
kp: [cpp-memory-mgmt]
primary_kp: cpp-memory-mgmt
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-mem-fd-001/
---
实现 FileGuard：构造时接受 FILE*，析构时 fclose 并设全局标志 g_closed=true。move-only。tests 通过 g_closed 验证。

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <cstdio>

extern bool g_closed;

class FileGuard {
public:
    explicit FileGuard(std::FILE* f) noexcept;
    ~FileGuard();
    FileGuard(FileGuard&& other) noexcept;
    FileGuard& operator=(FileGuard&& other) noexcept;
    FileGuard(const FileGuard&) = delete;
    FileGuard& operator=(const FileGuard&) = delete;
    std::FILE* get() const noexcept;
private:
    std::FILE* f_;
};
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## 解析
`FileGuard` 用 RAII 管理 `FILE*`，析构时若指针非空就 `fclose` 并设置 `g_closed = true`。移动构造/赋值要转移文件指针并把源对象置空，避免两个对象重复关闭同一文件。移动赋值前还要关闭当前已持有的文件，`get()` 只返回当前裸指针不转移所有权。
