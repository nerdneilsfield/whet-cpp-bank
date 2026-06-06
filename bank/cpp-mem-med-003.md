---
qid: cpp-mem-med-003
type: single
kp: [cpp-memory-mgmt]
difficulty: medium
answer_key: C
---

关于 placement new 和对象的生命周期管理，哪个说法正确？

```cpp
alignas(std::string) char buf[sizeof(std::string)];
auto* p = new (buf) std::string("hello");
// 使用 p ...
// 清理阶段：
```

A. `delete p;` 即可正确释放内存，因为 `p` 指向 `buf` 的首地址
B. `operator delete(p, buf)` 可以正确回收内存
C. 必须显式调用 `p->~std::string()` 再让 `buf` 自动析构，不能使用 `delete`
D. placement new 创建的对象只能用 `delete[]` 释放

---

**解析：**

placement new 只负责在已分配的缓冲区上构造对象，不分配内存。对应的"销毁"必须调用析构函数手动结束对象生命周期，而**不能使用 `delete`**（`delete` 会调用 `operator delete(void*)` 尝试释放底层内存，但 `buf` 是栈上数组，调用 `delete` 导致未定义行为）。

正确的清理方式：
```cpp
p->~std::string();   // 手动销毁对象
// buf 随作用域结束自动析构（char 不需要析构）
```

这一模式在自定义内存池、arena allocator 等场景中很常见——构造/析构由用户管理，内存分配/回收由分配器管理，两者解耦。

## Explanation

正确答案是 C，placement new 只在已有缓冲区中开始对象生命周期，并没有分配可由 `delete` 回收的内存。清理时必须显式调用 `p->~std::string()` 结束对象生命周期，然后让底层 `buf` 按其原本规则离开作用域。把 placement new 得到的指针交给 `delete` 或 `delete[]` 都会把非堆内存当堆内存释放，属于未定义行为。
