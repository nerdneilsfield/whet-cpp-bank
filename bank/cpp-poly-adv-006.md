---
qid: cpp-poly-adv-006
type: single
kp: [cpp-polymorphism]
difficulty: medium
answer_key: B
---

在 64 位平台上，以下含虚函数的类对象，其内存布局中**第一个字段**是什么？

```cpp
struct Animal {
    virtual void speak();
    int age;
    double weight;
};

Animal a;
// &a 处的内存布局是？
```

A. `age`（int，4 字节），然后是 vptr
B. `vptr`（虚表指针，8 字节），然后是 `age`，然后是 `weight`
C. `weight`（double，8 字节），然后是 `vptr`，然后是 `age`
D. `vptr` 在对象末尾，不影响前面字段的偏移

---

**解析：**

主流 ABI（Itanium ABI，GCC/Clang 在 Linux/macOS 使用）规定：**vptr 位于对象起始处**（偏移 0）。

- `Animal` 对象布局（64位）：
  - `[0..7]`：vptr（8 字节，指向 `Animal` 的 vtable）
  - `[8..11]`：`age`（int，4 字节）
  - `[12..15]`：padding（4 字节，对齐 double）
  - `[16..23]`：`weight`（double，8 字节）
  - `sizeof(Animal) = 24`

- vptr 在头部的意义：多态调用 `p->speak()` 时，CPU 直接从 `p` 指向地址取前 8 字节得到 vtable 指针，无需加偏移，最快。

MSVC ABI 也将 vptr 置于起始处。
