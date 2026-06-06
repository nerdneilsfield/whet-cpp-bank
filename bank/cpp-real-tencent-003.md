---
qid: cpp-real-tencent-003
type: single
kp: [cpp-memory-mgmt]
primary_kp: cpp-memory-mgmt
difficulty: hard
answer_key: B
tags: [interview-real, tencent]
---
```cpp
struct Node {
    std::shared_ptr<Node> next;
    std::weak_ptr<Node>   prev;   // 使用 weak_ptr 避免循环引用
};

void test() {
    auto a = std::make_shared<Node>();
    auto b = std::make_shared<Node>();
    a->next = b;
    b->prev = a;
}
```
关于 weak_ptr 解决循环引用的原理，以下说法正确的是：

A. weak_ptr 拷贝时会增加 shared_ptr 的引用计数 1，所以可以安全引用对象
B. weak_ptr 不增加 shared_ptr 的引用计数（ref_count），但会增加 weak_count；当 ref_count 降为 0 时对象被销毁，weak_ptr 通过 lock() 检查发现对象已失效
C. weak_ptr 持有原始指针，性能更高
D. weak_ptr 和 shared_ptr 互斥，一个对象不能同时被两者引用

---

**解析：**

选 B。weak_ptr 是解决 shared_ptr 循环引用的关键工具。

**control block 中有两个计数：**
- `ref_count`（强引用计数）：shared_ptr 个数，控制**对象本身**何时析构
- `weak_count`（弱引用计数）：weak_ptr 个数 + 1（只要 ref_count > 0 就额外 +1），控制**control block 本身**何时释放

**工作流程：**
1. weak_ptr 拷贝 → weak_count++（不影响 ref_count）
2. 最后一个 shared_ptr 析构 → ref_count → 0 → 对象 delete，但 control block 保留
3. weak_ptr 调用 lock() → 检查 ref_count，若 0 返回空 shared_ptr，否则 atomic 增加 ref_count 返回新 shared_ptr
4. 最后一个 weak_ptr 析构 → weak_count → 0 → control block delete

**为什么解决循环引用？** 在双向链表中：
- 若 prev 用 shared_ptr：a.next=b, b.prev=a → a 和 b 互相强引用 → 两者的 ref_count 都至少为 1 → 永不析构 → 内存泄漏
- 若 prev 用 weak_ptr：b.prev=a 只增加 a 的 weak_count，不增加 ref_count → 外部最后一个引用消失后 a 和 b 都能被销毁

A 错，weak_ptr 不增加 ref_count（这是它的全部价值）。C 错，weak_ptr 内部仍持有 control block 指针，不是 raw pointer。D 错，weak_ptr 必须从 shared_ptr 构造。

**来源：** 腾讯后端 C++ 面试（参考：cppreference、Effective Modern C++ Item 20）