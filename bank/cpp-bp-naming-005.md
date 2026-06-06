---
qid: cpp-bp-naming-005
type: single
kp: [cpp-scope-linkage]
difficulty: medium
answer_key: C
---

某动态库 `libfoo.so` 导出函数：

```cpp
// libfoo v1
namespace foo {
    std::string format(int x);
}
```

v2 中增加了 `bool` 参数：

```cpp
// libfoo v2
namespace foo {
    std::string format(int x, bool pretty = false);   // 新增默认参数
}
```

旧客户端用 v1 头文件编译，链接到 v2 .so 时会发生什么？

A. 完全兼容，默认参数自动生效
B. 编译失败
C. 链接失败：函数符号 mangled name 不同（带 bool 参数），旧客户端找不到 `_ZN3foo6formatEi`
D. 运行时崩溃

---

## Explanation

C++ ABI 的关键概念：函数签名（包括参数类型）会被 **mangled** 进符号名。

- v1：`std::string foo::format(int)` mangles 为 `_ZN3foo6formatEi`（GCC Itanium ABI）
- v2：`std::string foo::format(int, bool)` mangles 为 `_ZN3foo6formatEib`

虽然 v2 提供了默认参数，从源码角度 `format(42)` 仍可调用，但 **mangled name 完全不同**。**默认参数是编译期填充的，不是 ABI 的一部分**。

旧客户端的二进制内 `call _ZN3foo6formatEi` 在 v2 .so 中找不到该符号 → 链接失败（`undefined reference` 或 dlopen 时 `symbol not found`）。

工程教训——**保持 ABI 稳定的常见手段**：

1. **不修改已有 export 函数签名**，新增功能用新名字：
```cpp
std::string format(int x);                    // v1 保留
std::string format_pretty(int x, bool p);     // v2 新增
```

2. **用 pImpl + 抽象类**隔离 ABI（虚函数表有自己的 ABI 兼容规则）：
```cpp
class Formatter {
public:
    virtual ~Formatter() = default;
    virtual std::string format(int x) = 0;
};
extern "C" Formatter* make_formatter();   // C 链接，稳定
```

3. **C ABI 接口层**：动态库导出的核心接口写成 `extern "C"`，因 C 没有 mangling。

4. **库版本号 / symbol versioning**：libstdc++ 用 .symver 标记每个符号的版本，老程序自动绑老符号。

5. **C++ 标准库本身**：libstdc++ 5 引入 dual ABI（`std::string` 的两个不兼容版本），靠 inline namespace `__cxx11` 区分，是教科书案例。
