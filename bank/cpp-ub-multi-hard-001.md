---
qid: cpp-ub-multi-hard-001
type: multi
kp: [cpp-undefined-behavior]
difficulty: hard
answer_key: [A, B, D]
---
关于严格别名规则（strict aliasing rule），以下说法正确的是哪些？

```cpp
float f = 1.0f;
int*   p = reinterpret_cast<int*>(&f);
int    x = *p;                            // (1)

uint32_t u = 0x42280000;
float    g = *reinterpret_cast<float*>(&u); // (2)

char* c = reinterpret_cast<char*>(&f);
char  b = *c;                              // (3)
```

A. (1) 是典型严格别名违例：通过 `int*` 访问 `float` 对象，是未定义行为；优化器可能因此生成意料之外的代码。
B. (3) 合法：标准明确允许通过 `char*`、`unsigned char*`、`std::byte*` 访问任意对象（"字符类型例外"）。
C. (2) 完全合法：从 `uint32_t` 到 `float` 的位重解释广泛使用，符合标准。
D. 安全的字节级类型双关（type-punning）应使用 `std::memcpy` 或 C++20 的 `std::bit_cast`，而非 `reinterpret_cast`。

---

**解析：**

A 正确：严格别名规则要求"通过某类型左值访问对象的动态类型必须是兼容类型"，`float` 对象通过 `int*` 访问违反规则，是 UB，优化器可假设两个指针不会别名而生成错位代码（GCC `-O2` 常出问题）。
B 正确：标准明确把字符类型作为别名规则的例外（[basic.lval]/11），通过 `char*`、`unsigned char*`、C++17 起的 `std::byte*` 访问任意对象都合法。
C 错误：(2) 同样违反严格别名规则，方向相反但本质一致——通过 `float*` 访问 `uint32_t` 对象同样是 UB；很多老代码这么写但严格来说不合标准（GCC 提供了 union 的扩展但不可移植）。
D 正确：`std::memcpy` 不涉及指针别名，标准明确把它视为字节复制，安全可移植；C++20 的 `std::bit_cast` 是 constexpr 友好的类型双关原语，要求源/目标同尺寸且 trivially copyable，是首选方案。

## Explanation

A、B、D 正确：严格别名规则禁止用不兼容类型的左值访问对象，例如通过 `int*` 读取 `float` 对象。字符类型和 `std::byte` 可用于观察对象表示，但不能把 `reinterpret_cast` 解引用当作安全位重解释。常见误区是因为某些平台“看起来能跑”，就忽略优化器基于别名规则做出的假设。
