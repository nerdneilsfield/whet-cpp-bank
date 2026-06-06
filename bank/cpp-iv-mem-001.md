---
qid: cpp-iv-mem-001
type: short
kp: [cpp-interview]
difficulty: medium
tags: [腾讯, 阿里, 字节跳动]
rubric:
  - 能说清 new/delete 调用构造/析构函数，malloc/free 不会
  - 知道 new 失败抛 std::bad_alloc，malloc 返回 nullptr
  - 说明 new 是运算符可重载，malloc 是 C 库函数
  - 明确不能交叉使用（new 配 delete，malloc 配 free）
  - 加分：提到 new(nothrow)、delete[] 与 new[] 匹配
---

# `new`/`delete` vs `malloc`/`free` 的区别？

## Explanation

`new`/`delete` 和 `malloc`/`free` 都用于动态内存分配，但有本质区别：

### 1. 构造/析构函数调用

`new` 在分配内存后**自动调用构造函数**，`delete` 在释放前**自动调用析构函数**。`malloc`/`free` 仅操作原始内存，不涉及对象生命周期。

```cpp
struct Foo {
    Foo()  { std::cout << "ctor\n"; }
    ~Foo() { std::cout << "dtor\n"; }
};

Foo* a = new Foo;     // 输出 "ctor"
delete a;             // 输出 "dtor"

Foo* b = (Foo*)malloc(sizeof(Foo));  // 无输出，对象未初始化
free(b);                              // 无输出，析构未执行
```

### 2. 失败处理

- `new` 失败抛出 `std::bad_alloc` 异常（或用 `new(std::nothrow)` 返回 `nullptr`）。
- `malloc` 失败返回 `nullptr`，需手动检查。

```cpp
try {
    int* p = new int[1000000000];
} catch (const std::bad_alloc& e) {
    std::cerr << e.what();
}

int* p = (int*)malloc(1000000000 * sizeof(int));
if (!p) { /* 处理失败 */ }
```

### 3. 运算符 vs 库函数

`new`/`delete` 是 C++ **运算符**，可以重载（`operator new`/`operator delete`）。`malloc`/`free` 是 C 标准库函数，无法重载。

### 4. 类型安全

`new` 返回正确类型指针，无需强转。`malloc` 返回 `void*`，C++ 中需强转。

### 5. 数组形式

`new[]` 对应 `delete[]`；若 `new[]` 后用 `delete`（非 `delete[]`），行为未定义（UB）。

### 6. 不可混用

`new` 申请的内存**必须用 `delete`** 释放，`malloc` 申请的**必须用 `free`**，混用是 UB。

| 特性 | `new`/`delete` | `malloc`/`free` |
|------|---------------|-----------------|
| 构造/析构 | 自动调用 | 不调用 |
| 失败行为 | 抛异常 | 返回 nullptr |
| 类型安全 | 是 | 否（void*） |
| 可重载 | 是 | 否 |
| 语言 | C++ | C/C++ |
