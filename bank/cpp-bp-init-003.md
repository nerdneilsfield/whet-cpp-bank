---
qid: cpp-bp-init-003
type: single
kp: [cpp-classes]
difficulty: medium
answer_key: B
---

下面类的构造函数初始化顺序，哪个最终对象状态正确？

```cpp
class Buffer {
    size_t cap_;
    char* data_;
    size_t size_;
public:
    Buffer(size_t n)
        : size_(0), data_(new char[n]), cap_(n)   // ← 注意写顺序
    {}
    ~Buffer() { delete[] data_; }
};
```

A. 顺序无所谓，按初始化列表写的顺序执行
B. 按成员声明顺序执行：cap_ → data_ → size_，cap_ 在 data_ 之前但代码看似 size_ 第一个
C. 编译错误
D. 按字段大小顺序

---

**解析：**

C++ 规则：**成员初始化顺序由声明顺序决定，与初始化列表书写顺序无关**。

声明顺序：`cap_`、`data_`、`size_`，因此实际执行顺序是：
1. `cap_(n)` — OK
2. `data_(new char[n])` — OK
3. `size_(0)` — OK

幸运的是，本例中各成员相互不依赖，结果正确。

**陷阱版**：
```cpp
class Buffer {
    char* data_;
    size_t cap_;
public:
    Buffer(size_t n) : cap_(n), data_(new char[cap_]) {}   // ← bug
};
```
书写顺序 `cap_ → data_`，但**实际执行顺序**是 `data_ → cap_`。`data_(new char[cap_])` 时 `cap_` 尚未初始化，读未初始化值是 **UB**，可能分配 0 或 4GB。

编译器警告：GCC/Clang 加 `-Wreorder` 会警告"member 'data_' will be initialized after 'cap_' [-Wreorder]"。**始终开启该警告**。

正确做法：
1. 初始化列表书写顺序与声明顺序保持一致
2. 默认成员初始化器（C++11）：`size_t cap_ = 0; char* data_ = nullptr;` 避免大部分问题
3. 编译选项：`-Wreorder -Werror=reorder`