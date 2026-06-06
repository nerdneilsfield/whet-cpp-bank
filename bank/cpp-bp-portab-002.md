---
qid: cpp-bp-portab-002
type: single
kp: [cpp-type-sizes]
difficulty: medium
answer_key: C
---

下列代码在 x86（little-endian）正常运行，部署到 PowerPC / 网络协议解析时崩了：

```cpp
struct Header {
    uint32_t magic;
    uint16_t version;
    uint16_t flags;
    uint32_t payload_size;
};

void parse(const uint8_t* buf) {
    Header* h = reinterpret_cast<Header*>(buf);
    if (h->magic == 0xDEADBEEF) {
        size_t size = h->payload_size;
        // ...
    }
}
```

A. 整型大小不一致
B. struct 内 padding 不同
C. Endianness 差异 + 可能违反 strict aliasing + 可能 misaligned access
D. uint32_t 不存在

---

## Explanation

这段代码有**三个独立的可移植性问题**，任一都可能让代码在不同平台行为不同：

**1. Endianness（字节序）：**
- x86/x86_64：little-endian
- PowerPC（默认）、网络字节序：big-endian
- 内存中的 `0xEFBEADDE` 字节序列在 little-endian 上读为 `0xDEADBEEF`，在 big-endian 上读为 `0xEFBEADDE`
- 解析网络协议必须用显式字节序函数：`ntohl`、`be32toh`

**2. Alignment（对齐）：**
- `uint32_t` 在多数 ABI 上要求 4 字节对齐
- `buf` 可能未对齐（如从 TCP 流中读取的字节）
- ARM、PowerPC、SPARC 等架构对 unaligned access **触发 bus error / SIGBUS**（x86 容忍但慢）

**3. Strict aliasing：**
- 通过 `Header*` 访问 `uint8_t*` 指向的内存违反 strict aliasing 规则（除了 `char*`/`unsigned char*`/`std::byte*`）
- 编译器可优化掉看似冗余的 load

**4. Padding / 内存布局**：
- 虽然 `Header` 中所有字段对齐已经良好，但 struct 可能在某些 ABI 上有 trailing padding
- 序列化/反序列化跨平台时不能依赖 struct memory layout

正确做法：

```cpp
#include <cstring>
#include <bit>          // C++20 bit_cast

uint32_t read_be32(const uint8_t* p) {
    return (uint32_t(p[0]) << 24) | (uint32_t(p[1]) << 16) |
           (uint32_t(p[2]) << 8)  | uint32_t(p[3]);
}

uint16_t read_be16(const uint8_t* p) {
    return (uint16_t(p[0]) << 8) | uint16_t(p[1]);
}

void parse(const uint8_t* buf) {
    uint32_t magic = read_be32(buf);
    if (magic == 0xDEADBEEF) {
        uint16_t version = read_be16(buf + 4);
        uint16_t flags   = read_be16(buf + 6);
        uint32_t payload_size = read_be32(buf + 8);
        // ...
    }
}
```

或用 `memcpy`（无 alignment 要求且不违反 aliasing）：

```cpp
uint32_t value;
std::memcpy(&value, buf, 4);          // 安全
value = ntohl(value);                  // 转字节序
```

正确答案 C。
