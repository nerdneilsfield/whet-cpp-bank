---
qid: cpp-real-tencent-001
type: single
kp: [cpp-memory-mgmt]
primary_kp: cpp-memory-mgmt
difficulty: hard
answer_key: D
tags: [interview-real, tencent]
---
```cpp
class Foo {
public:
    Foo() { std::cout << "ctor"; }
    ~Foo() { std::cout << "dtor"; }
};
int main() {
    Foo* p1 = (Foo*)malloc(sizeof(Foo));   // (A)
    Foo* p2 = new Foo;                      // (B)
    free(p1);                                // (C)
    delete p2;                               // (D)
}
```
关于 new/delete 与 malloc/free 的本质区别，以下说法**不正确**的是：

A. new 会调用构造函数，delete 会调用析构函数，malloc/free 不会
B. new 是 C++ 关键字（操作符），可被重载（operator new），malloc 是 C 库函数，不能被重载
C. new 分配失败抛 std::bad_alloc，malloc 失败返回 nullptr
D. malloc 在小内存使用 brk 系统调用，大内存使用 mmap；new 完全不依赖 brk/mmap，而是直接通过 syscall 分配

---

**解析：**

选 D（说法错误的项）。

**正确的本质区别：**

| 维度 | new/delete | malloc/free |
|------|-----------|-------------|
| 类型 | 操作符（可重载） | 库函数 |
| 构造/析构 | 会调用 | 不会调用 |
| 失败处理 | 抛 std::bad_alloc | 返回 nullptr |
| 类型安全 | 返回精确类型 T* | 返回 void* 需转换 |
| 内存来源 | **底层通常仍调 malloc** 或 operator new(底层是 malloc + sbrk/mmap) | brk/sbrk（小块）+ mmap（大块，通常 >128KB） |

**为什么 D 错？** new 的底层通常调用 `operator new`，而 `operator new` 默认实现是调用 `malloc`。所以 new 间接也走 brk/mmap。new 不是绕过 libc 直接 syscall 的。

**brk/mmap 选择阈值：** glibc malloc 默认在分配 >128KB（M_MMAP_THRESHOLD）时使用 mmap，否则用 brk 扩展堆顶。
- brk 优点：快（一次系统调用扩展大量内存）
- mmap 优点：释放后可立即返回 OS，不会产生堆碎片

A、B、C 都是正确表述。

**来源：** 腾讯 C++ 后端面试（参考：glibc malloc 源码、《C++ Primer》、cs-offer）

## Explanation

正确答案是 D。
选 D（说法错误的项）；正确的本质区别： 为什么 D 错？。
new 的底层通常调用 operator new，而 operator new 默认实现是调用 malloc；所以 new 间接也走 brk/mmap。
选 D（说法错误的项）。
