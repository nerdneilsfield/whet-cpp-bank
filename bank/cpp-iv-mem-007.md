---
qid: cpp-iv-mem-007
type: short
kp: [cpp-interview]
difficulty: hard
tags: [Google]
rubric:
  - 准确定义 placement new（在指定地址构造对象，不分配内存）
  - 说明典型使用场景（内存池、共享内存、栈上构造、嵌入式）
  - 知道销毁方式：必须**显式调用析构函数**，不能用 delete
  - 理解 placement new 不需要 #include 以外的头文件（<new>）
  - 加分：说明 std::launder 在 placement new 后重用的正确性问题（C++17）
---

# `placement new` 是什么？何时使用？如何正确销毁？

## Explanation

### 什么是 placement new

`placement new` 是 `operator new` 的一种特殊重载形式，**在调用者指定的已有内存地址上构造对象，不分配任何新内存**。

```cpp
#include <new>   // 必须包含，提供 placement new 声明

// 语法：new (地址) 类型(构造参数)
void* buf = ::operator new(sizeof(MyClass));   // 只分配原始内存
MyClass* obj = new (buf) MyClass(42);           // 在 buf 处构造
```

编译器将上面第二行展开为：直接调用 `MyClass::MyClass(42)`，`this` 指向 `buf`，**没有任何额外内存分配**。

### 典型使用场景

#### 1. 内存池（Pool Allocator）

```cpp
class Pool {
    alignas(std::max_align_t) char storage_[4096];
    size_t offset_ = 0;
public:
    void* alloc(size_t n, size_t align = alignof(std::max_align_t)) {
        offset_ = (offset_ + align - 1) & ~(align - 1);
        void* p = storage_ + offset_;
        offset_ += n;
        return p;
    }
};

Pool pool;
// 在内存池上构造对象，无堆分配开销
Widget* w = new (pool.alloc(sizeof(Widget))) Widget(1, 2);
```

#### 2. 共享内存 / mmap 区域

```cpp
void* shm = mmap(nullptr, sizeof(Config),
                 PROT_READ | PROT_WRITE,
                 MAP_SHARED | MAP_ANONYMOUS, -1, 0);
Config* cfg = new (shm) Config();   // 在共享内存中构造
```

#### 3. 栈上构造大对象（避免堆分配）

```cpp
alignas(MyObj) char stack_buf[sizeof(MyObj)];
MyObj* p = new (stack_buf) MyObj(args...);
// 用完后显式析构（见下文）
```

#### 4. 嵌入式 / 无堆环境

禁用动态内存分配的嵌入式系统中，placement new 是在静态缓冲区上构造 C++ 对象的唯一方式。

### 正确销毁：显式调用析构函数

**绝对不能用 `delete p`**——`delete` 会先调用析构函数，再释放 `p` 指向的内存；但该内存并非 `new` 分配的，`free` 会导致 UB（heap corruption 或崩溃）。

```cpp
// 正确销毁方式：显式调用析构，然后释放底层内存
p->~MyObj();                 // 步骤 1：显式析构（必须）
::operator delete(raw_ptr);  // 步骤 2：释放底层原始内存（如果是 operator new 分配的）
// 若底层是栈/静态缓冲区，步骤 2 不需要，缓冲区自动回收
```

完整示例：

```cpp
#include <new>
#include <iostream>

struct Foo {
    int val;
    Foo(int v) : val(v) { std::cout << "ctor " << v << "\n"; }
    ~Foo()               { std::cout << "dtor " << val << "\n"; }
};

int main() {
    // 分配原始内存
    void* raw = ::operator new(sizeof(Foo));

    // placement new 构造
    Foo* p = new (raw) Foo(99);
    std::cout << p->val << "\n";

    // 正确销毁
    p->~Foo();                  // 显式析构
    ::operator delete(raw);     // 释放原始内存
}
// 输出：ctor 99 / 99 / dtor 99
```

### C++17：`std::launder`

在同一地址重复 placement new 构造不同对象后，编译器可能因为指针"过期"而进行错误优化。`std::launder` 告诉编译器重新从指定地址取对象：

```cpp
Foo* p = new (buf) Foo(1);
p->~Foo();
Foo* p2 = new (buf) Foo(2);
// p2 = std::launder(reinterpret_cast<Foo*>(buf));  // C++17 严格别名场景需要
```
