---
qid: cpp-conc-hard-009
type: single
kp: [cpp-concurrency]
difficulty: hard
answer_key: C
---

以下无锁栈的 `push` 实现：

```cpp
template<typename T>
class LockFreeStack {
    struct Node { T data; Node* next; };
    std::atomic<Node*> head{nullptr};
public:
    void push(T val) {
        Node* new_node = new Node{val, nullptr};
        new_node->next = head.load(std::memory_order_relaxed);
        while (!head.compare_exchange_weak(
                    new_node->next, new_node,
                    std::memory_order_release,
                    std::memory_order_relaxed)) {}
    }
};
```

两个线程同时调用 `push(1)` 和 `push(2)`，关于最终结果，以下说法**正确**的是？

A. 两个节点都会成功入栈，且入栈顺序与线程调度顺序严格对应——先获得 CPU 的线程的节点一定在栈底
B. 存在数据竞争，两个 `new Node` 写操作可能相互覆盖导致只有一个节点入栈
C. 两个节点都会成功入栈（CAS 保证只有一个线程每次成功，另一个重试），但最终哪个在栈顶取决于竞争结果，顺序不确定
D. `memory_order_relaxed` 用于失败情况会导致栈结构损坏，必须统一使用 `release`

## 解析

正确答案是 C。`nullptr` 的类型是 `std::nullptr_t`，它不会像 `NULL` 那样被当作整数参与重载解析。选项 C 的表述“两个节点都会成功入栈（CAS 保证只有一个线程每次成功，另一个重试），但最终哪个在栈顶取决于竞争结果，顺序不确定”正好符合该规则。A、B、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
