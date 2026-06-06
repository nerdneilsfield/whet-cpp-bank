---
qid: cpp-taste-err-008
type: single
kp: [cpp-exceptions, cpp-memory-mgmt]
primary_kp: cpp-exceptions
difficulty: hard
answer_key: D
tags: [code-taste, best-practice]
---
一个函数接收"可能为 null"的指针参数，要处理 null 情况。四种写法的设计理念不同，哪个品味最好？

```cpp
// A
void process_a(const Widget* p) {
    if (!p) throw std::invalid_argument("p");
    do_process(*p);
}

// B
void process_b(const Widget* p) {
    if (!p) return;
    do_process(*p);
}

// C
void process_c(const Widget* p) {
    assert(p && "p must not be null");
    do_process(*p);
}

// D
void process_d(const Widget& p) {
    do_process(p);
}
```

A. A — 显式检测 null + 抛异常，明确告诉调用方"不能传 null"
B. B — "你说可能 null，我就容忍 null 啥也不做"
C. C — `assert` 在 debug 下帮你捕获 bug，release 时零开销
D. D — 不接受指针，只接受引用——类型系统直接排除 null

---

**解析：**

选 D。这道题考 **"用类型系统排除无效状态，而不是在运行时检查"**。

D 根本不在函数内部处理 null——函数签名 `const Widget&` **编译器保证 p 一定引用一个有效对象**。调用方如果只有一个指针，就必须 `process_d(*ptr)`——但在调用方地点！如果 `ptr` 可能是 null，他们自己要在调用前检查、自己决定怎么处理。**类型强制调用方负起责任，而不是把"忘记检查"的 bug 推到函数内部延续**。

逐一品味：

- **A**：在函数边界**检查 null 并抛异常**——这是调用方没检查时的"防御式"写法。问题在于：**调用方可能依赖了这个行为**，把"传 null 然后 catch"当正常流程，这又回到了"异常用于控制流"的陷阱。而且 `do_process(*p)` 在 if 检查之下其实可以放到 if 作用域里、返回 early，避免嵌套。整体是**能跑但不是最干净的**——检查 null 的成本每次都付，但 null 真的是调用方该处理的事。
- **B**："传 null 我就交作业啥也不做"——这是最可怕的沉默设计。调用方以为处理过了、拿到结果（或者没结果但也不报错）继续往下跑，然后 debug 三小时找不到原因。**`if (!p) return;` 把"null 是错误"变成了"null 是有效输入"**，等于说类型说反话。
- **C**：`assert` 在 C 时代是标准写法——Debug 测试阶段暴露错误、Release 上线时编译器删掉、零开销。**但 (1) 在 Release 里传 null 就是 UB**；(2) C++ 有更安全的 null 排除工具（引用），不需要再退回到 assert。**`assert` 应保留给"不可能发生的逻辑错误"（如 switch 的 default 分支），而不是"调用方可能传错"的边界检查。**

**核心识别点：**

- 看见函数参数是 `const T*` → 警觉 null 是合法值还是不合法值
- 不合法 null → 改签名 `const T&`（或 `T` by-value）
- 合法 null（C API / optional 参数）→ 保留指针但不要 `if (!p) return;`
- `assert(p)` 检查参数 → 警觉 Release 失效，用引用更好
- `if (!p) return;` 给函数逻辑引入 hidden state → 警觉沉默错误

**D 的签名本身就是对调用方的契约声明：我不需要处理 null，因为我根本不接受空的可能性。** 这是 C++ 引用比指针的"语义升级"最经典的应用——引用非空这一性质从 C 时代开始就是引用定义的一部分（Bjarne 原话："A reference should be implemented by a pointer, but it is not a pointer — references do not have a null value"）。

**来源：** 手写题。引用不可空是 C++ 语言定义的一部分（[dcl.ref]/§11.3.2）；C++ Core Guidelines I.4, F.7, P.5；assert 适用场景见 Scott Meyers *Effective Modern C++* Item 14 的 noexcept 讨论中也涉及了 assert 在 Release 中的失效。

## Explanation

正确答案是 D。这道题考 "用类型系统排除无效状态，而不是在运行时检查"。
逐一品味： A：在函数边界检查 null 并抛异常——这是调用方没检查时的"防御式"写法。
这道题考 "用类型系统排除无效状态，而不是在运行时检查"。
