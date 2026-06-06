---
qid: cpp-bp-portab-003
type: single
kp: [cpp-type-sizes]
difficulty: medium
answer_key: C
---

下列对齐相关代码哪个是**未定义行为**？

```cpp
// A
struct alignas(64) CacheAligned {
    int x;
};
CacheAligned ca;
assert(reinterpret_cast<uintptr_t>(&ca) % 64 == 0);

// B
alignas(16) char buf[16];
new (buf) double{3.14};
double d = *reinterpret_cast<double*>(buf);

// C
char buf[16];
new (buf) double{3.14};      // ← 这里
double d = *reinterpret_cast<double*>(buf);

// D
auto p = std::aligned_alloc(64, 1024);
free(p);
```

A. A
B. B
C. C：char[16] 无对齐保证，double 要求 8 字节对齐，placement new 在未对齐内存上构造是 UB
D. D

---

## Explanation

C++ 对齐规则：
- 每个类型有 `alignof(T)` 要求，通常等于 `sizeof(T)`（对基本类型）
- `double` 在多数平台上要求 8 字节对齐
- 创建/访问类型 T 对象的内存必须满足 T 的对齐要求，否则 UB

**逐个分析：**

- **A 正确**：`alignas(64)` 强制 CacheAligned 对象 64 字节对齐。OS-level 栈对齐通常 16 字节，alignas 提升到 64。
- **B 正确**：`alignas(16) char buf[16]` 让 buf 至少 16 字节对齐，>= double 的 8 字节要求。在 buf 上 placement new double 合法。
- **C 错误**：普通 `char buf[16]` 没有对齐保证（编译器可能给 1 字节对齐，char 的默认对齐）。在未对齐内存上 placement new double 是 UB——在 ARM/PowerPC 可能崩溃，在 x86 可能慢但"看起来工作"。
- **D 正确**：`std::aligned_alloc(alignment, size)`（C++17）保证返回 alignment 字节对齐的内存。**注意：size 必须是 alignment 的整数倍**，否则在某些平台是 UB（POSIX 要求）。

**常见对齐工具：**

```cpp
// C++11+ 编译期对齐
alignas(16) double aligned_doubles[100];

// C++11+ 类型对齐查询
constexpr size_t a = alignof(double);

// C++17 标准 aligned_alloc
void* p = std::aligned_alloc(64, 1024);

// C++17 std::aligned_storage（已 deprecated in C++23）
std::aligned_storage_t<sizeof(T), alignof(T)> buf;
new (&buf) T{};

// C++17 std::launder + alignas
struct alignas(64) Slot { std::byte data[64]; };

// 自定义 allocator
struct AlignedAllocator { ... };
```

**调试工具：**
- UBSan `-fsanitize=alignment` 能在运行时捕获错误对齐访问
- `-Wcast-align` 警告可能 unaligned 的 cast

**SIMD 场景**：AVX/AVX-512 加载/存储常要求 16/32/64 字节对齐：
```cpp
alignas(32) float vec[8];
__m256 v = _mm256_load_ps(vec);    // 必须对齐！
__m256 v = _mm256_loadu_ps(unaligned); // 容忍未对齐但慢
```

正确答案 C。
