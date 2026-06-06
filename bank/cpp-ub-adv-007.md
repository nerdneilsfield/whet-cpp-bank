---
qid: cpp-ub-adv-007
type: fill
kp: [cpp-undefined-behavior]
difficulty: medium
answer_key: 显式调用析构函数（p->~Foo()）；不需要（也不能）用 delete
---

在栈上用 `char` 数组 + placement new 构造对象时，对象生命周期结束时应该如何清理？填写横线处正确做法。

```cpp
#include <new>
#include <cstddef>

struct Foo {
    int x;
    Foo(int v) : x(v) {}
    ~Foo() { /* 释放资源 */ }
};

int main() {
    alignas(Foo) char buf[sizeof(Foo)];
    Foo* p = new (buf) Foo(42);   // placement new 构造

    // 使用对象...
    p->x = 100;

    // 结束生命周期：___________________________
    // 注意：___________________________（关于 delete）
}
```

---

**解析：**

placement new **不分配内存**，内存来自 `buf`（栈上）。因此：

1. **必须显式调用析构函数**来结束对象生命周期，释放对象持有的资源：
   ```cpp
   p->~Foo();
   ```

2. **绝不能使用 `delete p`**：`delete` = 析构 + `::operator delete()`（释放堆内存）。但 `buf` 是栈内存，对其调用 `::operator delete()` 是 UB。

3. `buf` 本身是栈变量，函数返回时自动销毁（内存自动回收），无需手动处理。

完整写法：
```cpp
alignas(Foo) char buf[sizeof(Foo)];
Foo* p = new (buf) Foo(42);
// ... 使用 p ...
p->~Foo();          // 显式析构，合法且必要
// buf 随函数栈帧销毁，无需 delete
```

对于平凡析构类型（trivially destructible），可以省略显式析构调用，但显式调用总是安全的。

## 解析

填入 `显式调用析构函数（p->~Foo()）；不需要（也不能）用 delete`，因为题目要求的是该规则下的精确表达或标准名称。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 常见误区是写出近似说法、旧式写法或省略必要的命名空间/符号，导致与答案含义不完全一致。
