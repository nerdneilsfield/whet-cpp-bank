---
qid: cpp-iv-move-002
type: short
kp: [cpp-interview]
difficulty: medium
tags: [阿里, Meta]
rubric:
  - 指出拷贝语义的核心开销：深拷贝导致堆内存分配 + memcpy
  - 移动语义的本质：资源所有权转移，O(1) 指针操作代替 O(n) 内存复制
  - 用 std::string 的内部布局（ptr/len/cap）说明拷贝 vs 移动的操作差异
  - 说明移动后源对象进入"有效但未指定"状态
  - 加分：提到 SSO（小字符串优化）下移动可能退化为拷贝
---

# 移动语义解决了什么问题？用 `std::string` 举例说明拷贝 vs 移动的开销差异。

## Explanation

### 问题背景：拷贝开销

C++03 中，将对象传入函数或从函数返回时，编译器只能调用**拷贝构造函数**。对于持有堆内存的对象（如 `std::string`），这意味着：

1. 分配等量堆内存
2. `memcpy` 复制所有字节
3. 复制完毕后，若是临时对象，原对象随即析构（白白分配又释放）

```cpp
std::string make_str() {
    std::string s(1000000, 'x'); // 1MB 字符串
    return s;                    // C++03：深拷贝 1MB，然后析构 s
}
std::string result = make_str(); // 又一次深拷贝
```

### std::string 内部布局

典型实现约等于：

```cpp
struct string_internal {
    char*  ptr;   // 指向堆上字符数组
    size_t len;
    size_t cap;
};
```

**拷贝构造**：

```
src:  [ptr=0x1000, len=1M, cap=1M]
         ↓  malloc(1M) + memcpy
dst:  [ptr=0x2000, len=1M, cap=1M]
// 成本：1次堆分配 + 1M 字节复制
```

**移动构造**：

```
src:  [ptr=0x1000, len=1M, cap=1M]
         ↓  仅复制三个字段，将 src.ptr 置 nullptr
dst:  [ptr=0x1000, len=1M, cap=1M]
src:  [ptr=nullptr, len=0, cap=0]   ← 源对象进入有效但空的状态
// 成本：三次赋值，O(1)
```

### 代码对比

```cpp
#include <string>
#include <utility>
#include <iostream>

std::string heavy(1'000'000, 'x');

void demo() {
    // 拷贝：分配新内存 + memcpy 1MB
    std::string a = heavy;            // copy ctor

    // 移动：仅转移指针，O(1)
    std::string b = std::move(heavy); // move ctor
    // 此后 heavy 为空字符串，不可依赖其内容
}
```

### 移动语义的意义

- **返回值优化（RVO/NRVO）**：编译器可自动省略拷贝，但移动语义是 RVO 不适用时的保底。
- **容器 resize**：`std::vector` 扩容时对元素批量 move，而非 copy，大幅降低时间复杂度常数。
- **所有权转移语义**：`std::unique_ptr` 只支持移动，通过移动语义强制表达独占所有权。

### 注意：SSO

大多数实现对短字符串（通常 ≤ 15 字节）做**小字符串优化（SSO）**，字符存在栈内，此时移动退化为拷贝，开销相同。面试中提到这一点会加分。
