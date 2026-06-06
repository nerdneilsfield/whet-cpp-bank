---
qid: cpp-hc-source-002
type: single
kp: [cpp-memory-mgmt, cpp-concurrency]
primary_kp: cpp-memory-mgmt
difficulty: hard
answer_key: B
tags: [interview-real, handcrafted, source-reading]
---
libc++ 中 `std::shared_ptr` 的 control block 关键字段简化如下：

```cpp
// libc++ __shared_weak_count 简化
class __shared_weak_count {
    long __shared_owners_;     // 强引用计数 - 1
    long __shared_weak_owners_; // 弱引用计数 - 1
public:
    void __add_shared() noexcept {
        __libcpp_atomic_refcount_increment(__shared_owners_);
    }
    bool __release_shared() noexcept {
        if (__libcpp_atomic_refcount_decrement(__shared_owners_) == -1) {
            __on_zero_shared();   // 析构被管理对象
            __release_weak();      // 弱引用 -1
            return true;
        }
        return false;
    }
};
```

注意 `__shared_owners_` 注释是 "强引用计数 **- 1**"。`shared_ptr<T> p(new T);` 创建后 `p.use_count() == 1`，但 control block 里这个字段是 `0`。**为什么 libc++ 要把计数减 1 存储？**

A. 节省 4 字节存储——`long` 改 `int` 不行但减 1 可以让初始值落入 cache 友好的区段
B. 让原子递减后**和 `-1` 比较**能命中处理器的 `dec + js`（带符号跳转）指令对，比"减 1 然后和 0 比"快一个比较周期
C. 因为标准要求 `weak_ptr` 计数从 0 起，强引用为对齐必须也从 0 起
D. 兼容历史版本的 `boost::shared_ptr` ABI

---

**解析：**

选 B。这是 libc++ 的微优化，源码注释里有写。

在 x86 上：
- `decl mem; jnz target`（"减 1 后非零则跳转"）是常见的循环结尾指令对
- `lock dec` 后 CPU 已经设置好 ZF/SF 标志位

如果计数从 1 起、递减后**和 0 比较**——CPU 已经设了标志位，但你还要再做一条 `cmp` 才能判 "是不是已经归零"。

如果计数从 0 起（实际值 = 真实计数 - 1）、递减后**和 -1 比较**——这等价于"减 1 后 SF==1 或 OF==1"，可以直接用 `js`/`jl` 一条跳转完成，省去 `cmp`。

源码里 `__libcpp_atomic_refcount_decrement(__shared_owners_) == -1` 编译成的汇编大致是：

```asm
lock; xaddl %eax, (%rdi)    ; eax=-1, returns old value
decl %eax                    ; eax = old - 1, sets flags
js    .L_zero                ; sign bit set => was 0 => now -1
```

一条 `js` 替代了 `cmp + jcc`，在热路径上每次 `shared_ptr` 析构都省一个 cycle。这种"偏移 -1 存储"在引用计数和信号量实现里是经典手法（Linux kernel 的 `atomic_dec_and_test` 是同样套路）。

A 错——`long` 仍是 8 字节，减 1 不省空间。C 错——标准没规定 control block 内部表示，只规定外部 `use_count()` 行为。D 错——libc++ 与 boost 的 ABI 不兼容，没有兼容动机。

**来源：** 手写题，参考 libc++ `src/memory.cpp` 与 LLVM commit 历史中的 micro-optimization 讨论；x86 dec/js 指令对见 Intel SDM Vol.1 §6.7。
