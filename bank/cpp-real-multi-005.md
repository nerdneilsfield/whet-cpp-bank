---
qid: cpp-real-multi-005
type: multi
kp: [cpp-memory-mgmt, cpp-special-members]
primary_kp: cpp-memory-mgmt
difficulty: medium
answer_key: [A, B, C]
tags: [interview-real, multi-vendor]
---
RAII（Resource Acquisition Is Initialization）作为 C++ 的核心资源管理范式，适用于以下哪些场景（多选）？

A. 文件句柄管理（`std::ifstream` 在析构时自动关闭）
B. 互斥锁的获取与释放（`std::lock_guard` 在析构时自动解锁）
C. 动态内存管理（`std::unique_ptr` 在析构时自动 delete）
D. 静态全局对象的初始化顺序控制
E. 跨进程共享内存的生命周期管理（直接 mmap 后无需做任何包装）

---

**解析：**

正确答案：**A、B、C**。

**RAII 的核心思想：** 把资源绑定到对象生命周期。构造函数获取资源，析构函数释放资源。利用 C++ 自动析构机制保证**异常安全**和**资源不泄漏**。

**经典 RAII 应用：**

**A 正确：** `std::ifstream f("a.txt")` 打开文件，离开作用域自动调用析构函数关闭文件。即使作用域中抛异常，栈展开时也会析构 → 文件一定关闭。

**B 正确：** `std::lock_guard<std::mutex> lk(m)` 构造时加锁，析构时解锁。无论函数怎么退出（return / 异常）都会解锁，避免死锁。

**C 正确：** `std::unique_ptr<T> p(new T)` 析构时 delete。new 失败也只是抛异常，没有任何资源泄漏。

**D 错误：** 静态对象的**初始化顺序**是另一个问题（"static initialization order fiasco"），RAII 不能解决。需要用"Construct on First Use Idiom"（首次访问时构造的函数局部静态变量）。

**E 错误：** 直接 mmap 不算 RAII。RAII 需要**封装**资源到一个对象中。要做的话应该写：
```cpp
class SharedMem {
    void* ptr_;
    size_t len_;
public:
    SharedMem(size_t n) : len_(n) { ptr_ = mmap(...); }
    ~SharedMem() { munmap(ptr_, len_); }
    // 禁用拷贝...
};
```

**RAII 优势：**
1. 异常安全（栈展开自动释放）
2. 防止资源泄漏（包括 leaked memory、leaked file handle、leaked socket、leaked lock）
3. 简化代码（无需写 try-finally 或显式 cleanup）
4. 与 move semantics 完美配合（unique_ptr 移动 = 转移资源所有权）

**来源：** 跨厂高频 C++ 习语（参考：Stroustrup《The C++ Programming Language》, Effective C++ Item 13-14）