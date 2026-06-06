---
qid: cpp-move-semantics-multi-hard-005
type: multi
kp: [cpp-move-semantics]
difficulty: hard
answer_key: [A, C, D]
---
关于 return 语句中的隐式移动（implicit move on return），以下说法正确的是哪些？

```cpp
struct Big { Big(const Big&); Big(Big&&); };

Big f1() { Big b; return b; }                 // (1)
Big f2(Big b) { return b; }                   // (2) 函数参数
Big f3() { Big b; return std::move(b); }       // (3)
Big f4(Big& b) { return b; }                  // (4) 引用形参
```

A. (1) 中 `b` 是函数体内的非 volatile 局部对象，return 时编译器先尝试 NRVO（拷贝省略）；若不能 elide，则按右值处理触发隐式 move。
B. (3) 是推荐写法：显式 `std::move` 始终比 (1) 性能更好，因为它强制移动避免拷贝。
C. (2) 中 `b` 是函数形参（同样是自动存储期对象），return 时也享受隐式 move 规则——返回时按右值处理。
D. (4) 中 `b` 是引用形参（非局部对象），不享受隐式 move，必然走拷贝构造。

---

**解析：**

A 正确：标准 [class.copy.elision] 规定，当 return 表达式是一个引用了"自动存储期的非 volatile 对象"（且不是函数形参之外的引用）的 id-expression 时，先尝试拷贝省略（NRVO），不能省略则按右值处理触发 move。
B 错误：`return std::move(b)` 会**阻止 NRVO**（因为 return 表达式不再是简单的 id-expression），强制至少一次 move；而 `return b;` 在能 NRVO 时是零成本。所以 (1) 通常比 (3) 更优，加 `std::move` 反而是负优化（典型反模式）。
C 正确：C++11 起函数形参也算作合格的局部对象（具备自动存储期），同样享受隐式 move 规则；但形参由于已经构造在调用者栈帧中，无法 NRVO，但可以 move。
D 正确：引用形参指向的对象不属于该函数的局部对象（生命周期不归本函数所有），不能视为右值，因此 `return b;` 走拷贝构造，这也是 Effective Modern C++ 中明确提到的规则。