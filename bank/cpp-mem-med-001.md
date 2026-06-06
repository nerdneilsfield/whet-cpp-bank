---
qid: cpp-mem-med-001
type: single
kp: [cpp-memory-mgmt]
difficulty: medium
answer_key: C
---

下列代码中，`Node` 之间互相持有 `shared_ptr`，程序退出时两个节点的内存会如何处理？

```cpp
struct Node {
    std::shared_ptr<Node> next;
    ~Node() { std::puts("dtor"); }
};

int main() {
    auto a = std::make_shared<Node>();
    auto b = std::make_shared<Node>();
    a->next = b;
    b->next = a;
}
```

A. 两个 `Node` 都会被析构，输出两次 "dtor"
B. 编译器会检测循环引用并在退出前回收
C. 两个 `Node` 都泄漏，引用计数始终为 1，不输出 "dtor"
D. 行为未定义，可能崩溃

---

**解析：**

`shared_ptr` 用引用计数管理对象，对象只在引用计数归零时析构。`a->next = b` 让 `b` 指向的对象引用计数变为 2，`b->next = a` 同理。`main` 结束时局部 `a`、`b` 析构使各自计数减 1，但还剩 1（被对方的 `next` 持有），永远不会归零，析构函数不被调用，内存泄漏。

解决方法是把循环中的一条边改成 `std::weak_ptr<Node>`，例如父子结构里子节点用 `weak_ptr` 持有父节点。`weak_ptr` 不增加强引用计数，循环被打破后引用计数能正常归零。

## Explanation

正确答案是 C，两个 `Node` 通过 `shared_ptr` 互相强引用，局部变量离开作用域后各自引用计数仍为 1。引用计数不归零，析构函数不会执行，所以不会输出 `dtor`。常见误区是以为 `shared_ptr` 能自动处理环；实际需要把其中一条拥有关系改为 `weak_ptr`。
