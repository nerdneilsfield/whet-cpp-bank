---
qid: cpp-bp-error-005
type: single
kp: [cpp-exceptions]
difficulty: medium
answer_key: A
---

以下代码的"错误"是什么？

```cpp
class ScopedFile {
    FILE* f_;
public:
    ScopedFile(const char* path) : f_(fopen(path, "r")) {
        if (!f_) throw std::runtime_error("open failed");
    }
    ~ScopedFile() { fclose(f_); }
};

void process() {
    try {
        ScopedFile f("data.txt");
        auto buf = std::make_unique<char[]>(1ul << 40); // 1TB
        read_file(f, buf.get());
    } catch (...) {
        std::cerr << "error\n";
    }
}
```

A. 无问题（正确使用了 RAII，资源安全）
B. 析构函数不应该调 fclose
C. 构造函数抛异常时不应该调 fclose
D. 析构应标 noexcept(false) 防止 terminate

---

## Explanation

这里是一个**教科书式正确的 RAII 设计**，但很多工程师会误判。

关键点：构造函数中 `f_` 成功的 `fopen` 后再抛异常（`bad_alloc`），`~ScopedFile()` **不会被调用**（对象构造尚不完全）。但 `f_` 已经指向有效文件，这是个**资源泄漏**。

等等——仔细看代码：构造函数抛异常只在 `fopen` 失败时（`if (!f_) throw`）。如果 `fopen` 成功则 `f_` 有效，构造函数执行完毕。而 `bad_alloc` 是在 `process()` 的 `make_unique` 中抛出的，此时 `f` 对象已经完全构造好，离开作用域时会正确调用 `~ScopedFile()`。

因此这个代码**没有问题**。选项 B、C、D 都是常见误解：
- B：RAII 析构调 fclose 正是正确做法
- C：构造函数在 `f_` 被赋值前就抛了，无需清理
- D：析构默认 noexcept，调 fclose 不会抛异常

这是 RAII+异常安全的最佳实践案例。
