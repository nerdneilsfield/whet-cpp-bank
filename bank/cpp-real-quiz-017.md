---
qid: cpp-real-quiz-017
type: single
kp: [cpp-cpp14-17, cpp-types]
primary_kp: cpp-cpp14-17
difficulty: medium
answer_key: B
tags: [interview-real, cppquiz, language-lawyer]
---
根据 C++17 标准，以下程序中 `a` 和 `b` 的类型分别是？

```cpp
#include <string>
using namespace std::string_literals;

auto a = "hello";       // (1)
auto b = "hello"s;      // (2)
```

A. 都是 `std::string`
B. `a` 是 `const char*`，`b` 是 `std::string`
C. 都是 `const char*`
D. 编译错误（`s` 不是合法后缀）

---

**解析：**

(1) `"hello"` 是字符串字面值，类型 `const char[6]`，`auto` 推导时数组退化为指针 → `const char*`。

(2) `"hello"s` 是 C++14 引入的**用户自定义字面值**（[lex.ext]）。需要 `using namespace std::string_literals;` 或 `std::literals` 才能识别，类型是 `std::string`。

后缀对照：
- `"x"s` → `std::string`
- `"x"sv` → `std::string_view`（C++17）
- `1s` → `std::chrono::seconds`（在 chrono_literals 命名空间下）

**来源：** C++14 [lex.ext]；C++17 standard library [basic.string]
