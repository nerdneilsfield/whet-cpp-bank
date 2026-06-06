---
qid: cpp-iv-sys-008
type: short
kp: [cpp-interview]
difficulty: hard
tags: [阿里, Google]
rubric:
  - 准确定义 COW：写时才真正复制，读时共享同一份数据
  - 说明 std::string COW 的历史实现方式（引用计数 + 共享 buffer）
  - 指出 C++11 废弃 COW 的核心原因：多线程竞争 + iterator/reference 失效问题
  - C++11 SSO（Small String Optimization）作为替代方案
  - 加分：举出其他 COW 使用场景（fork、写时快照、Redis BGSAVE）
---

# 什么是 Copy-on-Write（COW）？`std::string` 为何曾用 COW，C++11 后为何废弃？

## Explanation

### Copy-on-Write 定义

**Copy-on-Write（写时复制，COW）** 是一种延迟复制策略：多个对象共享同一份底层数据，**只在某个对象真正需要修改时才实际复制**。读操作全部共享，避免不必要的内存分配和数据拷贝。

```
s1 = "hello world"     ← 分配内存，refcount=1
s2 = s1                ← 不复制内存，refcount=2，s1/s2 指向同一 buffer
s2[0] = 'H'            ← COW 触发：复制 buffer，refcount 各自回到 1，再修改
```

### std::string 的历史 COW 实现

在 C++11 之前，许多 STL 实现（GCC libstdc++ 直到 GCC 4.x）将 `std::string` 实现为 COW：

```
[refcount | capacity | size | data ...]
      ↑
  buffer 头部存引用计数
```

- 拷贝构造/赋值：只递增 `refcount`，O(1)。
- 修改（`operator[]`、`begin()` 等非 const 操作）：检查 `refcount > 1` 时执行"深拷贝"，再修改。

### C++11 废弃 COW 的原因

**1. 多线程数据竞争（最关键）**

多线程同时读取共享 `std::string` 的 `refcount`（即使只是读操作，`begin()` / `c_str()` 也可能触发 "detach" 检查）存在竞争条件。用锁保护会使所有字符串操作都引入同步开销，实际上比直接复制更慢。

C++11 要求 `std::string` 的只读操作（`const` 成员函数）在多线程中无需外部同步即可并发安全，COW 实现无法满足此要求。

**2. iterator 和引用失效问题**

```cpp
std::string s1 = "hello";
std::string s2 = s1;           // COW：共享 buffer
const char *p = s1.c_str();   // p 指向共享 buffer
s2[0] = 'H';                   // s2 触发 COW，s2 得到新 buffer
// p 仍然有效，但若实现有误，p 可能在 s2 detach 后成为悬空指针
// 标准对此的规定本就模糊，COW 实现容易出 bug
```

**3. 性能实际上不总是更好**

COW 的收益只在**大字符串、频繁拷贝、极少修改**的场景下体现。现代程序中短字符串极其普遍，COW 的引用计数检查反而是额外开销。

### 替代方案：SSO（Small String Optimization）

C++11 标准实际上通过**隐式禁止 COW**（要求 `s[i]` 的 `const` 和非 `const` 重载在不同地址）鼓励实现 SSO：

- 字符串 ≤ 15（或 22）字节：直接存储在 `std::string` 对象的栈内存中，无堆分配，O(1) 拷贝。
- 字符串 > 阈值：堆分配，正常深拷贝语义。

SSO 对短字符串的实际性能远优于 COW，且线程安全，无引用失效风险。

### COW 的其他合法使用场景

| 场景 | 说明 |
|------|------|
| Linux `fork()` | 父子进程共享页表，写时才复制物理页（OS 级 COW） |
| Redis `BGSAVE` | fork 子进程做持久化，写时复制保证快照一致性 |
| 写时快照（Copy-on-Write B-Tree） | LMDB、MVCC 数据库的页级 COW |
| `std::shared_ptr` + 不可变数据 | 手动 COW：修改前先 `make_unique_copy` |

结论：COW 不是坏模式，但在 C++ `std::string` 这个特定场景下，多线程语义 + 标准 iterator 失效规则 + SSO 的崛起，共同使它被彻底淘汰。
