---
qid: cpp-iv-mem-005
type: short
kp: [cpp-interview]
difficulty: medium
tags: [Google, Meta, 阿里]
rubric:
  - 准确定义 RAII：资源生命周期与对象生命周期绑定
  - 能举出完整的代码示例（构造获取，析构释放）
  - 说明异常安全性是 RAII 的核心价值
  - 知道标准库中的 RAII 实例（unique_ptr、lock_guard、fstream 等）
  - 加分：说明 RAII 在多资源管理时的正确顺序（构造顺序的逆序析构）
---

# RAII 原则是什么？举一个完整代码示例。

## 参考答案

### 定义

**RAII（Resource Acquisition Is Initialization，资源获取即初始化）**：将资源（内存、文件句柄、锁、套接字等）的生命周期绑定到对象的生命周期。

- **构造函数**：获取资源（打开文件、分配内存、加锁）。
- **析构函数**：释放资源（关闭文件、释放内存、解锁）。

C++ 保证：无论函数正常返回还是异常抛出，局部对象的析构函数**一定会被调用**。RAII 利用这个保证实现自动资源管理。

### 不用 RAII 的问题

```cpp
void bad_example() {
    FILE* f = fopen("data.txt", "r");
    if (!f) return;

    process(f);      // 如果这里抛异常……
    fclose(f);       // ← 永远不会执行，文件泄漏！
}
```

### 完整 RAII 示例：文件资源包装器

```cpp
#include <cstdio>
#include <stdexcept>
#include <string>

class FileGuard {
public:
    // 构造：获取资源
    explicit FileGuard(const std::string& path, const char* mode)
        : file_(std::fopen(path.c_str(), mode))
    {
        if (!file_)
            throw std::runtime_error("Failed to open: " + path);
    }

    // 析构：释放资源（一定会执行）
    ~FileGuard() {
        if (file_) {
            std::fclose(file_);
            file_ = nullptr;
        }
    }

    // 禁止拷贝（资源所有权唯一）
    FileGuard(const FileGuard&)            = delete;
    FileGuard& operator=(const FileGuard&) = delete;

    // 允许移动
    FileGuard(FileGuard&& o) noexcept : file_(o.file_) { o.file_ = nullptr; }
    FileGuard& operator=(FileGuard&& o) noexcept {
        if (this != &o) {
            if (file_) std::fclose(file_);
            file_ = o.file_;
            o.file_ = nullptr;
        }
        return *this;
    }

    FILE* get() const { return file_; }

private:
    FILE* file_;
};

void good_example() {
    FileGuard fg("data.txt", "r");   // 构造时打开
    process(fg.get());               // 即使抛异常……
}  // ← fg 析构，文件自动关闭，无论如何
```

### 标准库中的 RAII 组件

| 资源 | RAII 封装 |
|------|-----------|
| 堆内存 | `std::unique_ptr`, `std::shared_ptr` |
| 互斥锁 | `std::lock_guard`, `std::unique_lock` |
| 文件流 | `std::fstream`（析构时自动关闭） |
| 线程 | `std::jthread`（C++20，析构时自动 join） |

### 多资源时的顺序

```cpp
struct MultiResource {
    LockGuard   lock;   // 先构造
    FileGuard   file;   // 后构造
    // 析构顺序：file 先析构，lock 后析构（与构造相反）
};
```

RAII 是 C++ 异常安全编程的基石，也是现代 C++ "零开销抽象"的典型体现。
