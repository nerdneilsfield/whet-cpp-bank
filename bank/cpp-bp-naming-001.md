---
qid: cpp-bp-naming-001
type: single
kp: [cpp-scope-linkage]
difficulty: medium
answer_key: B
---

下列两种 "TU 内私有函数" 写法，哪个**更符合现代 C++ 推荐**？

```cpp
// 写法 1
static int helper(int x) { return x * 2; }

// 写法 2
namespace {
    int helper(int x) { return x * 2; }
}

// （两者都放在 .cpp 文件里）
```

A. 1 更好，static 关键字更短
B. 2 更好，匿名命名空间是 C++ 推荐方式，且对类型/模板也有效
C. 等价，纯风格选择
D. 1 是 C 风格，C++ 中无效

---

## 解析

历史上 C 用 `static` 限制符号到 TU 内部链接。C++03 一度 **deprecate** 了命名空间作用域的 `static`，推动匿名命名空间。但 C++11 撤回了 deprecation。

两者**对函数等价**（都产生内部链接），但匿名命名空间更优：

1. **对类型也有效**：`static class Foo {};` 是错误的。但 `namespace { class Foo {}; }` 让 Foo 也成为 TU-local。
2. **对模板也有效**：static 不能修饰类模板/函数模板特化（语言规则），匿名命名空间可以。
3. **对常量**：C++17 起 `static constexpr int N = 10;` 也可以，但匿名命名空间统一所有类型的隐藏方式。
4. **可读性**：匿名命名空间集中声明所有 TU 私有的实体，让"哪些是私有"一目了然：

```cpp
// foo.cpp
namespace {
    constexpr int kBufSize = 4096;
    struct State { ... };
    int compute(int x) { ... }
    State g_state;   // TU-local 全局变量
}

void public_api() { ... }
```

注意：
- **不要在头文件中使用匿名命名空间**——每个包含头文件的 TU 会得到独立副本，违反 ODR 的初衷且占用空间
- 头文件中"私有"实体应放 `namespace detail`（明确语义，不强制隐藏）

正确答案 B。