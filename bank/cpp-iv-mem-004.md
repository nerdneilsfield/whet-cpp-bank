---
qid: cpp-iv-mem-004
type: short
kp: [cpp-interview]
difficulty: medium
tags: [华为, 腾讯]
rubric:
  - 解释内存对齐的定义（地址是类型大小的整数倍）
  - 说明 CPU 访问非对齐内存的代价（多次总线事务或异常）
  - 理解结构体对齐规则（成员对齐 + 整体对齐到最大成员）
  - 正确使用 alignas/alignof 语法
  - 加分：说明 #pragma pack 用途及副作用（性能下降、可移植性差）
---

# 内存对齐是什么？为什么需要？`alignas`/`alignof` 怎么用？

## Explanation

### 什么是内存对齐

内存对齐要求：**某类型 T 的变量地址必须是 `sizeof(T)`（或其对齐要求）的整数倍**。

例如 `int`（4 字节）要求地址对 4 字节对齐：0x0、0x4、0x8 合法，0x1、0x3 非法。

### 为什么需要对齐

1. **硬件限制**：多数 CPU 总线宽度固定（32/64 位），非对齐访问需要两次总线事务并拼接数据，带来 2× 性能损失。部分架构（ARM 旧版、SPARC）非对齐访问直接触发总线错误（Bus Error / SIGBUS）。
2. **原子性**：对齐的读写在大多数平台是原子的（x86 保证对齐的 8 字节读写原子性），非对齐不保证。
3. **SIMD 要求**：SSE/AVX 指令要求 16/32/64 字节对齐，否则崩溃或性能大幅下降。

### 结构体对齐规则

1. 每个成员按自身对齐要求放置（之前插入填充字节 padding）。
2. 结构体整体大小对齐到**最大成员的对齐值**。

```cpp
struct Bad {
    char  a;   // 1 byte, offset 0
    // 3 bytes padding
    int   b;   // 4 bytes, offset 4
    char  c;   // 1 byte, offset 8
    // 3 bytes padding
};
// sizeof(Bad) = 12（不是 6！）

struct Good {
    int   b;   // 4 bytes, offset 0
    char  a;   // 1 byte, offset 4
    char  c;   // 1 byte, offset 5
    // 2 bytes padding
};
// sizeof(Good) = 8
```

### `alignof` — 查询对齐要求

```cpp
static_assert(alignof(int)    == 4);
static_assert(alignof(double) == 8);
static_assert(alignof(char)   == 1);

struct S { double d; char c; };
static_assert(alignof(S) == 8);  // 最大成员 double 的对齐
```

### `alignas` — 指定对齐要求

```cpp
// 变量对齐到 64 字节（cache line 大小，避免 false sharing）
alignas(64) int cache_line_var;

// 类型对齐要求
struct alignas(16) SimdVec {
    float data[4];
};
static_assert(alignof(SimdVec) == 16);

// 栈上分配对齐内存（C++11 起合法）
alignas(32) char buf[256];
```

### `#pragma pack` — 紧凑布局（慎用）

```cpp
#pragma pack(push, 1)
struct Packet {   // 网络包，必须紧密布局
    uint8_t  type;
    uint32_t seq;
    uint16_t len;
};  // sizeof = 7，无 padding
#pragma pack(pop)
```

> **副作用**：访问非对齐成员时有性能损失；在严格对齐平台（ARM）上可能崩溃。仅用于需要与外部二进制格式精确匹配的场景（网络协议、文件格式）。
