---
qid: cpp-cast-multi-hard-002
type: multi
kp: [cpp-casting]
difficulty: hard
answer_key: [A, B, D]
---
关于类型双关（type punning）的几种方式 `std::bit_cast`、`std::memcpy`、`union`，以下说法正确的是哪些？

```cpp
float f = 1.0f;
// (1) C++20
uint32_t a = std::bit_cast<uint32_t>(f);

// (2)
uint32_t b;
std::memcpy(&b, &f, sizeof(f));

// (3) C 风格 union
union U { float f; uint32_t u; };
U x; x.f = 1.0f;
uint32_t c = x.u;
```

A. (1) `std::bit_cast` 是 C++20 引入的、专为类型双关设计的原语，要求源/目标类型同尺寸且 trivially copyable；可在 constexpr 上下文使用。
B. (2) `std::memcpy` 是标准明确允许的字节级复制方式；编译器会把对小对象的 memcpy 优化为寄存器搬运，性能与直接强转相当。
C. (3) `union` 类型双关在 C++ 中**完全合法**；标准明确允许通过 `union` 不同字段访问彼此（与 C 一致）。
D. `reinterpret_cast<uint32_t*>(&f)` 然后解引用违反严格别名规则，是 UB；以上三种方式比它都安全。

---

**解析：**

A 正确：`std::bit_cast<To>(From)` 要求 `sizeof(To)==sizeof(From)` 且二者 trivially copyable；它是 constexpr 函数，可在编译期完成位重解释，是 C++20 的推荐方式。

B 正确：`std::memcpy` 不涉及指针别名概念（标准把它定义为字节复制），是合规的类型双关方式；现代编译器对小尺寸 memcpy 做强优化，常常生成单条 mov 指令，无运行时开销。

C 错误：C++ 与 C 在这一点上**不同**。C99 起允许 union 类型双关（通过非活跃成员读取），但**C++ 标准未明确允许**——通过非活跃 union 成员读取严格说是 UB（仅 GCC 等编译器以扩展形式支持）。可移植代码应避免该用法。

D 正确：`*reinterpret_cast<uint32_t*>(&f)` 通过 `uint32_t` 左值访问 `float` 对象违反严格别名规则，是 UB；上述三种方式中 (1)(2) 完全合法，(3) 是 C 扩展但不可移植，整体均比 reinterpret_cast 更安全。

## Explanation

A、B、D 正确：`std::bit_cast` 和 `std::memcpy` 是标准支持的字节级类型双关方式，不违反严格别名规则。C++ 中通过非活跃 union 成员读另一种类型并不具备与 C 完全相同的可移植保证。常见误区是把 `reinterpret_cast` 后解引用当作“只看位模式”，但它仍通过错误类型的左值访问对象，属于 UB。
