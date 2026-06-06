---
qid: cpp-iv-smart-002
type: short
kp: [cpp-interview]
difficulty: medium
tags: [阿里, Google]
rubric:
  - 循环引用导致 use_count 永不归零，内存泄漏场景描述
  - weak_ptr 不增加强引用计数，只持有控制块的弱引用
  - 通过 lock() 升级为 shared_ptr，升级失败返回 nullptr
  - 典型场景：树/图的父子节点双向引用，观察者模式
  - expired() 检查对象是否已销毁
---

# Q: `weak_ptr` 的作用？如何解决 `shared_ptr` 的循环引用？代码演示。

## 参考答案

### 循环引用问题

两个 `shared_ptr` 互相持有对方，导致引用计数永远不为 0，内存永远无法释放：

```cpp
#include <memory>
#include <iostream>

struct Node {
    std::shared_ptr<Node> next;   // 强引用 → 循环
    ~Node() { std::cout << "~Node\n"; }
};

int main() {
    auto a = std::make_shared<Node>();
    auto b = std::make_shared<Node>();
    a->next = b;   // b.use_count = 2
    b->next = a;   // a.use_count = 2
    // main 结束：a、b 局部 shared_ptr 析构
    // a.use_count 2→1，b.use_count 2→1
    // 两个对象都不会被释放 → 内存泄漏！
    // "~Node" 永远不会打印
}
```

### 用 `weak_ptr` 打破循环

```cpp
#include <memory>
#include <iostream>

struct Node {
    std::weak_ptr<Node> next;    // 弱引用 → 不增加 use_count
    ~Node() { std::cout << "~Node\n"; }
};

int main() {
    auto a = std::make_shared<Node>();
    auto b = std::make_shared<Node>();
    a->next = b;   // b.use_count 仍为 1（weak 不加）
    b->next = a;   // a.use_count 仍为 1

    // main 结束：
    // a 局部 shared_ptr 析构 → a.use_count 1→0 → ~Node
    // b 局部 shared_ptr 析构 → b.use_count 1→0 → ~Node
    // 两次 "~Node" 正常打印，无泄漏
}
```

### `weak_ptr` 的核心 API

```cpp
std::shared_ptr<Node> sp = std::make_shared<Node>();
std::weak_ptr<Node>   wp = sp;

// 检查对象是否存活
if (!wp.expired()) {
    // 升级为 shared_ptr（线程安全的原子操作）
    if (auto locked = wp.lock()) {
        locked->doSomething();
    }
}

// 或直接用 lock() 的返回值判空
if (auto sp2 = wp.lock()) {
    // sp2 有效
} else {
    // 原始对象已析构
}
```

### 使用场景

| 场景 | 说明 |
|------|------|
| 树/图的父子双向引用 | parent 用 `shared_ptr`，child 的 parent 指针用 `weak_ptr` |
| 观察者（Observer）模式 | Subject 持有 `weak_ptr<Observer>` 列表，Observer 销毁后自动失效 |
| 缓存（对象池） | 缓存持有 `weak_ptr`，外部无人使用时自动释放 |

**关键点：** `weak_ptr` 增加控制块的 `weak_count`，不增加 `use_count`。对象析构后控制块仍存活直到所有 `weak_ptr` 也销毁，`lock()` 升级会检查 `use_count > 0`，原子地将其 +1 或返回空指针。
