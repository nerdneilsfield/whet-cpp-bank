---
qid: cpp-cast-hard-005
type: single
kp: [cpp-casting]
difficulty: hard
answer_key: A
---

多重继承下指针转换需要调整偏移：

```cpp
struct A { int a; };
struct B { int b; };
struct D : A, B { int d; };

D obj;
B* pb = &obj;
A* pa = static_cast<A*>(reinterpret_cast<D*>(pb));   // ①
A* pa2 = reinterpret_cast<A*>(pb);                    // ②
```

关于 ① 与 ② 的差异，下列正确的是？

A. ① 是正确做法：`static_cast` 知道 `D` 与 `A`、`B` 的继承关系，会按需做指针偏移调整，最终 `pa` 指向 `obj` 中 `A` 子对象的正确地址。② 直接 `reinterpret_cast` 把 `B*` 的位模式当作 `A*` 解释，得到的 `pa2` 指向 `obj` 内 `B` 子对象的地址——把它当作 `A*` 用就是访问错位的内存
B. 两者效果相同，因为 `reinterpret_cast` 等价于 `static_cast`
C. 都是 UB
D. ② 是 UB 但 ① 也会失败，因为 `D` 是私有继承

## 解析

多重非虚继承下的对象布局：`D` = `[A 子对象][B 子对象][D 自身成员]`（声明顺序）。从 `D*` 转到 `A*`：偏移 0；转到 `B*`：偏移 `sizeof(A)`。`static_cast`（包括隐式转换）在继承层次内**自动插入这种指针调整**。所以 `static_cast<A*>(static_cast<D*>(pb))` 正确还原为 `A*`。

`reinterpret_cast` 则完全跳过类型系统——它把指针的位模式当作目标类型解释，不做偏移调整。`reinterpret_cast<A*>(pb)` 得到的指针仍指向原 `B` 子对象的地址，把它当作 `A*` 访问就是访问错位的字节（`A::a` 被解读为 `B::b` 所在位置）。这是多重继承下 `reinterpret_cast` 极常见的陷阱。