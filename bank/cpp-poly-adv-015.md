---
qid: cpp-poly-adv-015
type: fill
kp: [cpp-polymorphism]
difficulty: hard
answer_key: "sizeof(D) == 32（64位平台：两个vptr各8字节 + int各4字节 + padding，共32字节）"
---

在 64 位平台上，推断以下多重继承类 `D` 的 `sizeof`，并解释内存布局：

```cpp
struct A {
    virtual void fa();
    int a;
};

struct B {
    virtual void fb();
    int b;
};

struct D : A, B {
    void fa() override;
    void fb() override;
    int d;
};

// sizeof(A) = ?
// sizeof(B) = ?
// sizeof(D) = ?
```

填写三个 `sizeof` 值，并描述 `D` 对象的内存布局。

---

**解析：**

**sizeof(A)** = 16：vptr_A（8）+ `int a`（4）+ padding（4）= 16。
**sizeof(B)** = 16：vptr_B（8）+ `int b`（4）+ padding（4）= 16。

**sizeof(D)** 的关键：`D` 多重继承 `A` 和 `B`，**两个基类各有自己的 vtable**，因此 `D` 的对象中有**两个 vptr**。

`D` 的内存布局（Itanium ABI）：

```
[0..7]   vptr_A → D 对 A 部分的 vtable（含 D::fa）
[8..11]  A::a（int）
[12..15] padding
[16..23] vptr_B → D 对 B 部分的 vtable（含 D::fb）
[24..27] B::b（int）
[28..31] D::d（int）
[32..？] 可能 padding（取决于最大对齐=8，32已对齐，无需）
```

**sizeof(D) = 32**。

注意：`A*` 指针与 `D*` 相同（偏移 0），`B*` 指针指向 `D` 对象内偏移 16 处。`static_cast<B*>(d_ptr)` 会将指针值加 16，这是多重继承指针转换的重要陷阱。

## Explanation

填空应为 `sizeof(D) == 32（64位平台：两个vptr各8字节 + int各4字节 + padding，共32字节）`，因为这是题干所问概念或语法在 C++ 中的标准写法。多态题的关键是区分静态类型与动态类型：只有通过基类指针或引用调用虚函数时，才会发生运行期动态分派。常见误区是把普通成员函数、对象切片、构造/析构期调用也当成完整的虚调用场景。 常见误区是写出近似术语、别名或只写部分符号；填空题通常要求与答案键精确对应。
