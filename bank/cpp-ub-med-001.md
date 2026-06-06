---
qid: cpp-ub-med-001
type: single
kp: [cpp-undefined-behavior]
difficulty: medium
answer_key: C
---
下列循环在优化器眼中可能被改写成无限循环或被直接删除，原因是？

```cpp
bool f(int x) {
    int i = x;
    while (i + 1 > i) { ++i; }   // 期望溢出后退出
    return true;
}
```

A. `while` 写法没问题，循环退出后返回 true
B. 编译器报警告，但运行无异常
C. 有符号整数溢出是未定义行为，编译器可假设 `i+1 > i` 恒成立，从而把循环视为无条件成立
D. 优化器会自动加上溢出检查保护程序

---

**解析：**

C++ 规定有符号整数溢出是未定义行为（UB），编译器据此可以**假设 UB 不会发生**——即 `i+1` 永远不会溢出，于是 `i+1 > i` 在数学上恒为真。基于这一假设，整个循环条件被优化为 `true`，循环成为死循环；甚至更激进地，调用 `f(x)` 后续代码因不可达被删。这类“UB-driven optimization”是真实事故源（如 Linux 内核 CVE）。要做溢出检测应使用无符号、`__builtin_add_overflow`、`<numeric_limits>` 或 `<intsafe>` 等可移植手段。
