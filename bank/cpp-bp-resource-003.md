---
qid: cpp-bp-resource-003
type: single
kp: [cpp-memory-mgmt]
difficulty: medium
answer_key: D
---

在异常安全方面，以下读取文件内容的代码哪个选项有问题？

```cpp
// 读取文件到 string
std::string read_all(const char* path) {
    FILE* f = fopen(path, "rb");
    if (!f) throw std::runtime_error("open fail");

    fseek(f, 0, SEEK_END);
    auto size = ftell(f);
    rewind(f);

    // 哪个选项有异常安全问题？
    // A
    std::string buf(size, '\0');
    fread(buf.data(), 1, size, f);
    fclose(f);
    return buf;

    // B
    auto buf = std::make_unique<char[]>(size);
    fread(buf.get(), 1, size, f);
    fclose(f);
    return std::string(buf.get(), size);
}
```

A. A：std::string 构造可能抛 bad_alloc，之后 fclose 不调，文件泄漏
B. B：make_unique 构造可能抛 bad_alloc，之后 fclose 不调
C. 两个都安全
D. 两个都不安全，但 A 更差

---

## Explanation

两个选项都有一个核心问题：`fopen` 和 `fclose` 之间的代码可能抛异常，导致 `fclose` 被跳过，fd 泄漏。但 RAII 就是为了解决这个的。

- A：`std::string(size, '\0')` 在构造时分配内存，若 `bad_alloc` 抛出了，`fclose(f)` 确实不会被调用。并且 `fread` 也可能失败而不报异常。
- B：`make_unique<char[]>(size)` 类似，若分配抛出也跳过 `fclose`。即使分配成功，`fread` 不抛异常，所以 B 在这个路径上安全，但分配路径仍有问题。

本质上两者都不安全。**正确答案 D** 因为 A 在 fread 后还要调 fclose，但 A 的构造路径比 B 短，不过都很差。

正确做法——始终用 RAII 包裹资源：
```cpp
struct FileCloser {
    void operator()(FILE* f) const { if (f) fclose(f); }
};
using FilePtr = std::unique_ptr<FILE, FileCloser>;

std::string read_all(const char* path) {
    FilePtr f{fopen(path, "rb"), FileCloser{}};
    if (!f) throw std::runtime_error("open fail");
    fseek(f.get(), 0, SEEK_END);
    auto size = ftell(f.get());
    rewind(f.get());
    std::string buf(size, '\0');
    auto nread = fread(buf.data(), 1, size, f.get());
    buf.resize(nread);
    return buf;  // f 随 unique_ptr 析构自动 fclose
}
```
