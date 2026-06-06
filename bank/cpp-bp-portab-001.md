---
qid: cpp-bp-portab-001
type: single
kp: [cpp-type-sizes]
difficulty: medium
answer_key: B
---

下列哪段代码在 32-bit 和 64-bit 平台行为可能**不同**，导致 bug？

```cpp
// A
int x = 100;
int y = x * 2;

// B
std::vector<int> v(1'000'000);
int total = std::accumulate(v.begin(), v.end(), 0);

// C
size_t n = v.size();
for (size_t i = 0; i < n; ++i) { ... }

// D
auto sz = sizeof(int);
```

A. A
B. B：accumulate 的初值是 int，求和过程中临时变量是 int（32-bit），可能溢出。在 64-bit 平台也是同一个问题，但更隐蔽（int 仍是 32-bit）
C. C
D. D

---

## Explanation

实际上 B 这段代码在 32-bit 和 64-bit 上**行为完全一致**——`int` 在两个平台上通常都是 32 位（4 字节），溢出阈值约 21 亿。

但 B 仍然是 bug——`std::accumulate(begin, end, init)` 的累加器类型由 `init` 的类型决定。`accumulate(..., 0)` 中 `0` 是 `int`，累加器是 `int`，**累加过程中可能溢出**而不报错。

100 万个 int，假设平均值 3000，总和已超 int 范围。这是工程中**最常见的 accumulate bug**。

正确写法：

```cpp
// 用 long long 累加
long long total = std::accumulate(v.begin(), v.end(), 0LL);

// 或用 size 范围相关的类型
auto total = std::accumulate(v.begin(), v.end(), int64_t{0});

// 浮点求和：double
double sum = std::accumulate(v.begin(), v.end(), 0.0);
```

实际上 32 vs 64 bit 平台差异的真正陷阱：

| 类型 | 32-bit | 64-bit (Linux LP64) | 64-bit (Windows LLP64) |
|------|--------|---------------------|------------------------|
| `int` | 4 | 4 | 4 |
| `long` | 4 | **8** | 4 |
| `long long` | 8 | 8 | 8 |
| `size_t` | 4 | 8 | 8 |
| `ptrdiff_t` | 4 | 8 | 8 |
| `void*` | 4 | 8 | 8 |

- **Linux/macOS 是 LP64**：long 是 8 字节
- **Windows 是 LLP64**：long 仍是 4 字节
- 写 `long` 用作 8 字节整数在 Windows 上爆掉

正确做法：
1. 整数类型用 `<cstdint>` 中的固定宽度类型：`int32_t`, `int64_t`, `uint8_t`
2. 容器大小用 `size_t`
3. 指针差值用 `ptrdiff_t`
4. 永远不用 `long`（除非接口要求）

正确答案 B。
