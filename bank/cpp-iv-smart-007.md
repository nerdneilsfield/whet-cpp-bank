---
qid: cpp-iv-smart-007
type: short
kp: [cpp-interview]
difficulty: hard
tags: [字节跳动]
rubric:
  - 用裸指针构造多个 shared_ptr 会创建多个独立控制块，引用计数各自为 1
  - 每个控制块归零时各自调用 delete，导致双重释放（double-free）
  - 正确做法：shared_ptr 之间通过拷贝/赋值共享同一控制块
  - enable_shared_from_this 解决成员函数内需要 shared_ptr<this> 的问题
  - 不要将 shared_ptr 管理的对象地址再传给裸 delete
---

# Q: `shared_ptr` 和裸指针混用的危险：双重释放场景演示。

## 参考答案

### 场景一：同一裸指针构造两个独立 `shared_ptr`

这是最常见的陷阱：两个 `shared_ptr` 各自持有同一裸指针，但拥有**各自独立的控制块**，引用计数各为 1。

```cpp
#include <memory>
#include <iostream>

struct Widget {
    ~Widget() { std::cout << "~Widget\n"; }
};

int main() {
    Widget* raw = new Widget();

    std::shared_ptr<Widget> sp1(raw);  // 控制块A，use_count=1
    std::shared_ptr<Widget> sp2(raw);  // 控制块B，use_count=1（独立！）

    // 离开作用域：
    // sp2 析构 → use_count(B)→0 → delete raw   ← 第一次释放
    // sp1 析构 → use_count(A)→0 → delete raw   ← 第二次释放，UB！
    // 输出 "~Widget" 两次，程序崩溃或堆损坏
}
```

**编译运行后行为：** 大概率 segfault 或 abort（heap corruption detected）。

### 场景二：用拷贝共享控制块（正确做法对比）

```cpp
int main() {
    std::shared_ptr<Widget> sp1 = std::make_shared<Widget>();
    std::shared_ptr<Widget> sp2 = sp1;  // 拷贝：共享同一控制块
    // sp1.use_count() == 2, sp2.use_count() == 2

    // 离开作用域：
    // sp2 析构 → use_count 2→1
    // sp1 析构 → use_count 1→0 → delete，一次，正确
}
```

### 场景三：成员函数内 `shared_ptr<this>` 错误用法

```cpp
struct Bad {
    std::shared_ptr<Bad> get_self() {
        return std::shared_ptr<Bad>(this);  // 又一个独立控制块！
    }
};

auto p = std::make_shared<Bad>();
auto p2 = p->get_self();  // 两个控制块共享同一对象 → double-free
```

**正确做法：继承 `enable_shared_from_this`**

```cpp
#include <memory>

struct Good : std::enable_shared_from_this<Good> {
    std::shared_ptr<Good> get_self() {
        return shared_from_this();  // 复用已有控制块，use_count++
    }
};

auto p = std::make_shared<Good>();
auto p2 = p->get_self();  // 同一控制块，use_count=2，安全
```

### 场景四：手动 `delete` 已被 `shared_ptr` 管理的对象

```cpp
auto sp = std::make_shared<int>(42);
int* raw = sp.get();
delete raw;   // ← 手动释放
// sp 析构时再次 delete → double-free
```

**规则总结：**

| 危险操作 | 后果 |
|----------|------|
| `shared_ptr<T>(raw_ptr)` 调用两次 | 双重释放 |
| `shared_ptr<T>(this)` 在成员函数中 | 双重释放 |
| `delete sp.get()` | 双重释放 |
| 从 `shared_ptr` 取出裸指针，再创建新 `shared_ptr` | 双重释放 |

**黄金规则：** 裸指针只应在**一个地方**交给 `shared_ptr`，之后所有 `shared_ptr` 只通过拷贝/赋值传播。永远不要用 `sp.get()` 的返回值再构造新的 `shared_ptr`。
