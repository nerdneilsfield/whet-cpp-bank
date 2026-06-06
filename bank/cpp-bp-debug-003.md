---
qid: cpp-bp-debug-003
type: single
kp: [cpp-build-tools]
difficulty: medium
answer_key: C
---

下面代码用 `assert` 检查不变量，发布构建（`-DNDEBUG`）时会发生什么？

```cpp
#include <cassert>

bool pop(Queue& q, int& out) {
    assert(q.size() > 0);              // 不变量检查
    out = q.front();
    q.pop_front();
    return true;
}

void process(Queue& q) {
    int x;
    assert(pop(q, x));                  // 注意：把函数调用放进了 assert
    use(x);
}
```

A. 不变量检查正常生效，性能略有损失
B. NDEBUG 下所有 assert 失效，但函数调用本身仍执行
C. NDEBUG 下 `assert(expr)` 整体被 `#define` 替换为空，**expr 完全不被求值**，导致 pop 不被调用，x 未初始化
D. NDEBUG 下 assert 改为抛异常

---

## 解析

C 标准库 `<cassert>` 的 `assert` 宏定义大致是：

```c
#ifdef NDEBUG
#  define assert(expr) ((void)0)
#else
#  define assert(expr) ((expr) ? (void)0 : __assert_fail(#expr, ...))
#endif
```

**NDEBUG 下整个 `(expr)` 被替换为空**——expr 的副作用（函数调用）完全消失。

这是 C/C++ 长期以来最容易踩坑的陷阱之一：

```cpp
assert(pop(q, x));         // bug! release 下 pop 不被调用
assert(initialize_db());   // bug! release 下 db 未初始化
assert(++counter == 5);    // bug! release 下 counter 不增
```

正确做法：

**1. assert 中只放纯谓词，不放有副作用的表达式：**
```cpp
bool ok = pop(q, x);
assert(ok);    // OK，分离副作用和检查
```

**2. 区分"前置条件"和"业务逻辑"：**
```cpp
// 前置条件 → assert
void f(int n) {
    assert(n > 0);   // 程序员错误，release 不必检查
    ...
}

// 业务错误 → 异常 / 错误码
auto cfg = load_config();
if (!cfg) throw std::runtime_error("config invalid");   // 用户错误，必须检查
```

**3. 使用专门的 expect 宏：**
```cpp
#define EXPECT(cond) if (!(cond)) std::abort()   // 在 release 也生效
// 或 Microsoft GSL: Expects(cond), Ensures(cond)
```

**4. C++20 contracts**（暂时未发布）：会用 `[[expects: cond]]` / `[[ensures: cond]]` 语法。

工程教训：
- `assert` 是**调试期检查**，不是错误处理
- 永远在 Release+NDEBUG 模式下也跑测试，提前发现这种 bug
- 用 `static_assert` 替代编译期检查（永远生效）

正确答案 C。