---
qid: cpp-ub-adv-003
type: single
kp: [cpp-undefined-behavior]
difficulty: medium
answer_key: B
---

下列哪种方式是**正确的**位级重解释（type punning），在 C++ 中不引发 UB？

```cpp
float f = 3.14f;

// 方式 A
int a = *reinterpret_cast<int*>(&f);

// 方式 B
int b;
std::memcpy(&b, &f, sizeof(b));

// 方式 C
int c = *(int*)(&f);

// 方式 D（C++20）
int d = static_cast<int>(f);
```

A. 方式 A，reinterpret_cast 即为"位级重解释"的标准用法
B. 方式 B，memcpy 是标准认可的类型双关（type punning）手段
C. 方式 C，C 风格强转与 reinterpret_cast 等价，均合法
D. 方式 D，static_cast 可直接转换位模式

---

**解析：**

| 方式 | 结果 |
|------|------|
| A / C | 违反 strict aliasing，UB；编译器可能优化掉整个读取 |
| B | 合法：`memcpy` 只操作字节，不违反别名规则；编译器在两端大小相同时通常会内联为单条 `mov` |
| D | `static_cast<int>(3.14f)` 是**数值转换**（截断为 3），不是位模式重解释 |

C++20 新增 `std::bit_cast<int>(f)` 作为编译期可用的类型双关方案，与 `memcpy` 语义相同但更符合语言习惯：
```cpp
int e = std::bit_cast<int>(f);  // C++20，合法，constexpr 友好
```

`memcpy` 路线从 C++03 起已被主流编译器优化，是跨标准版本最可靠的做法。
