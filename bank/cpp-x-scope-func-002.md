---
qid: cpp-x-scope-func-002
type: single
kp: [cpp-scope-linkage, cpp-functions]
primary_kp: cpp-scope-linkage
difficulty: medium
answer_key: B
---

下列两个文件的链接结果如何？

```cpp
// --- a.cpp ---
static int helper(int x) { return x * 2; }     // (i) 文件作用域 static
int call_a(int x) { return helper(x); }

// --- b.cpp ---
static int helper(int x) { return x * 3; }     // (ii) 同名 static
int call_b(int x) { return helper(x); }

// --- main.cpp ---
int call_a(int);
int call_b(int);
int main() { return call_a(10) + call_b(10); }  // 期望 20 + 30 = 50
```

A. 链接失败：`helper` 多重定义
B. 链接成功，`main` 返回 50
C. 链接成功，但两个 `helper` 合并为一个，结果未定义
D. 链接成功，`main` 返回 60（两次都调用同一个版本）

---

**解析：**

在 **命名空间作用域** 上使用 `static` 关键字，会赋予标识符 **internal linkage（内部链接）**——意味着：

- 该名字 **只在所在翻译单元（TU）内可见**，不会暴露给链接器。
- 不同 TU 中的 `static helper` 是 **完全独立** 的实体，互不影响。

因此：
- `a.cpp` 中的 `helper` 只对 `call_a` 可见，返回 `x * 2`。
- `b.cpp` 中的 `helper` 只对 `call_b` 可见，返回 `x * 3`。
- 它们在符号表中不存在（或以本地符号存在），链接器看不到，自然不会冲突。

`main` 调用 `call_a(10) + call_b(10) = 20 + 30 = 50`。

**对比**：

| 关键字/位置                              | 语义                                                       |
| ---------------------------------------- | ---------------------------------------------------------- |
| 命名空间作用域 `static`                  | internal linkage（C++ 推荐用匿名 namespace 替代）          |
| 命名空间作用域 anonymous namespace       | internal linkage（C++ 首选方式）                           |
| 类内成员 `static`                        | 类的静态成员（与链接无关，需要 ODR 定义一次）              |
| 函数体内 `static`                        | static storage duration（在程序整个生命周期内只初始化一次） |
| 全局 `extern`                            | external linkage（默认行为，可显式声明）                   |
| `inline` 命名空间作用域                  | external linkage 但允许多重定义（要求内容相同）            |

C++ 现代风格优先使用：

```cpp
namespace {
    int helper(int x) { return x * 2; }   // 匿名 namespace，等价于 static
}
```

匿名 namespace 不只能用于函数，还能用于类型、变量，是更通用的封装机制。