---
qid: cpp-cast-med-003
type: single
kp: [cpp-casting]
difficulty: medium
answer_key: C
---

下列两段代码使用 `const_cast` 写入，行为分别是？

```cpp
// 片段 ①
int x = 10;
const int& r = x;
const_cast<int&>(r) = 20;

// 片段 ②
const int y = 10;
const int& r2 = y;
const_cast<int&>(r2) = 20;
```

A. ① 和 ② 都合法
B. ① 和 ② 都是 UB
C. ① 合法，② 是 UB
D. ① 是 UB，② 合法

---

**解析：**

`const_cast` 只能去掉/添加 cv 限定，并不改变所指向对象的**实际类型**。能否通过去掉 const 后写入，取决于**原对象本身**是否真的是 const。

片段 ① 中 `x` 本身是非 const 的 `int`，`r` 只是一个 const 引用绑定到它；通过 `const_cast` 去掉 const 后写入，相当于直接修改 `x`，完全合法，事后 `x == 20`。

片段 ② 中 `y` 本身就是 const `int`，原对象的实际类型是 const 的；通过 `const_cast` 去掉 const 后写入是 UB（[dcl.type.cv]）。编译器还可能把 const 对象放进只读段，或假设其值永不变化并进行常量传播，写入要么崩溃要么导致后续读取仍得到旧值。

## Explanation

正确答案为 C，因为“① 合法，② 是 UB”符合题干所问的 C++ 规则或代码执行结果。A、B、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。类型转换题要区分编译期转换、运行期检查、cv 限定和底层位模式重解释。
