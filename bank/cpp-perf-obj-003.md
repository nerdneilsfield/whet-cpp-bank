---
qid: cpp-perf-obj-003
type: single
kp: [cpp-stl-basics, cpp-memory-mgmt]
primary_kp: cpp-stl-basics
difficulty: hard
answer_key: A
tags: [performance, code-taste]
---

要构造并返回 1 千万个**最长 15 字符**的短字符串。下面四种字符串类型功能等价，哪个最值得采用？

```cpp
// A
std::vector<std::string> v;
v.reserve(N);
for (int i = 0; i < N; ++i) {
    std::string s;
    s += 'k'; s += std::to_string(i % 1000);
    v.push_back(std::move(s));
}

// B
class HeapString {
    char* p_; std::size_t n_;
public:
    HeapString(const char* src) { n_ = std::strlen(src); p_ = new char[n_+1]; std::memcpy(p_, src, n_+1); }
    // ... move/copy ctor/dtor ...
};
std::vector<HeapString> v;
v.reserve(N);
for (int i = 0; i < N; ++i) {
    char buf[16];
    std::snprintf(buf, 16, "k%d", i % 1000);
    v.emplace_back(buf);
}

// C
std::vector<std::unique_ptr<std::string>> v;
v.reserve(N);
for (int i = 0; i < N; ++i)
    v.push_back(std::make_unique<std::string>("k" + std::to_string(i % 1000)));

// D
std::vector<std::string> v;
v.reserve(N);
for (int i = 0; i < N; ++i)
    v.emplace_back("k" + std::to_string(i % 1000));
```

A. A — 用 std::string，构造后 move 进 vector
B. B — 自己写 HeapString，每次 new[] 持有
C. C — 用 unique_ptr<std::string> 完全堆分配
D. D — emplace_back 直接构造

---

**解析：**

选 A 或 D（都依赖 SSO，A/D 性能等价，A 更明示是 SSO 友好长度，**取 A**）。这道题考的是"std::string 的 small string optimization"——短字符串完全栈/inline 存储、不触发堆分配。

逐一品味：

- **A**：`std::string` 在主流实现（libstdc++、libc++、MSVC STL）都有 SSO：短字符串（libc++ 22 字节、libstdc++ 15 字节、MSVC 15 字节，按 64-bit）直接存在 string 对象内部、**零堆分配**。本题字符串最长 "k999" = 4 字符 << 阈值，全部走 SSO。构造 string 是几条 MOV + 设置 size。后 push_back 通过 move 进 vector，**SSO 字符串的 move 也是字段 copy 而非指针偷取**（因为数据在对象内），但 string 在 SSO 路径上 move = memcpy ~24 字节。1e7 次 ≈ 240 MB 流量、零堆分配。**最快路径**。
- **B**：自己写的 HeapString 没有 SSO——**每次都 `new char[n+1]`**。1e7 次小堆分配是 allocator 的灾难（malloc 锁、free list 碎片化、metadata 开销 16+ 字节/分配）。即便用 jemalloc/tcmalloc 也比 SSO 慢 **5–20 倍**，且总占用内存膨胀 3–5 倍（metadata + free list overhead）。
- **C**：在 A 的基础上再加一层堆分配——unique_ptr 的 `new std::string(...)` **额外**分配 sizeof(string) ~32 字节，再加上 string 自己可能的 SSO/heap 数据。每个 string 比 A 多一次堆分配、vector 里多一次指针追逐。比 A 慢 **3–8 倍**且占用 vector 之外的内存。
- **D**：`emplace_back("k" + std::to_string(...))` 中的 `"k" + std::to_string(...)` 还是构造一个 string 临时（同样走 SSO），再传给 emplace 的 string 构造参数（参数也是 string，所以是 move）。和 A 的差别只在一次 move 是否能 elide。**性能基本等同 A**。但代码上 A 更清晰展示了 SSO 路径，D 略隐式（emplace 接受啥参数得想）。

A/D 都对，取 A 作为标准答案。重点是**不要拒绝 std::string**——它已经为你做了短字符串优化。

**核心识别点：**
- 看见自己写"持有 char* + size"的字符串类 → 警觉是不是重新发明了 std::string 且**没有 SSO**
- 看见 `unique_ptr<std::string>` → 几乎一定是过度间接，**string 本身就是值类型容器**
- 短字符串（< 15 字符）的 std::string：零堆分配、构造/拷贝/移动都是简单字段操作
- SSO 阈值在不同实现不同：libstdc++ 15、libc++ 22、MSVC 15 字节
- 1e7 次 `new` 是百毫秒级开销，1e7 次 SSO 是十毫秒级——一个量级差距

**来源：** Nicolai Josuttis, "The Nightmare of Move Semantics for Trivial Classes", CppCon 2017；libstdc++/libc++ basic_string 实现（_M_local_data）；Bjarne Stroustrup, "The C++ Programming Language" 4th ed., §19.3.3.
