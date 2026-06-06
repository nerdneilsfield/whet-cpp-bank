---
qid: cpp-x-cast-ub-001
type: single
kp: [cpp-casting, cpp-undefined-behavior]
primary_kp: cpp-casting
difficulty: medium
answer_key: B
---

下列两段代码使用 `const_cast` 写入，行为分别如何？

```cpp
// 片段 1
int x = 10;
const int& cr = x;
const_cast<int&>(cr) = 20;   // (1)

// 片段 2
const int y = 10;
const int& cr2 = y;
const_cast<int&>(cr2) = 20;  // (2)
```

A. (1) 和 (2) 都合法
B. (1) 合法；(2) 是未定义行为
C. (1) 是未定义行为；(2) 合法
D. (1) 和 (2) 都是未定义行为

---

## 解析

`const_cast` 只移除引用/指针上的 `const` 限定符，**并不改变所指对象的本质类型**。

[dcl.type.cv]/4：通过 non-const 路径修改 **原本被声明为 `const` 的对象**，是未定义行为。判断依据是 **底层对象的声明**，而非引用/指针的 const 性。

- **(1) 合法**：底层对象 `x` 声明为 `int`（非 const），`cr` 只是 const 引用。通过 `const_cast` 拿到 `int&` 后写入，等同于直接写 `x`。
- **(2) UB**：底层对象 `y` 声明为 `const int`。即便能在语法上把它的引用强制为 `int&`，实际写入是 UB。编译器可能把 `y` 放到只读内存（运行时段错误），或在编译期把所有 `y` 的读替换为常量 10（写入被忽略）。

教训：`const_cast` 的合法用途是「调用者保证拿到的对象本来就不是 const」，例如对外暴露 const 接口但内部需要写入；**绝不能用它绕开一个真正的 const 对象**。