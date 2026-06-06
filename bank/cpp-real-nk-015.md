---
qid: cpp-real-nk-015
type: single
kp: [cpp-memory-mgmt, cpp-classes]
primary_kp: cpp-memory-mgmt
difficulty: hard
answer_key: C
tags: [interview-real, nowcoder]
---

```cpp
class Bad {
public:
    std::shared_ptr<Bad> getSelf() {
        return std::shared_ptr<Bad>(this);  // ⚠️
    }
};

int main() {
    auto sp1 = std::make_shared<Bad>();
    auto sp2 = sp1->getSelf();
}
```

上述代码的问题及解决方案是：

A. 没问题，可以正常工作
B. sp1 和 sp2 共享同一个对象，引用计数会正确管理
C. **产生两个独立的控制块**，析构时会 **double free**；应该让 Bad 继承 `std::enable_shared_from_this<Bad>` 并用 `shared_from_this()`
D. 应该用 weak_ptr 替代 shared_ptr 来避免循环引用

---

**解析：**

`std::shared_ptr<Bad>(this)` 创建了一个**全新的控制块**，不知道 sp1 已经有一个。析构时两个控制块都会 delete 同一个 this 指针 → double free。

正确用法：
```cpp
class Good : public std::enable_shared_from_this<Good> {
public:
    std::shared_ptr<Good> getSelf() {
        return shared_from_this();
    }
};
```

`enable_shared_from_this` 内部有一个 `weak_ptr<T>`，当对象首次被 shared_ptr 管理时，这个 weak_ptr 被初始化。`shared_from_this()` 通过 `weak_ptr.lock()` 返回与原 shared_ptr 共享控制块的新 shared_ptr。

注意：在构造函数中调用 `shared_from_this()` 会抛 `bad_weak_ptr`，因为此时 weak_ptr 还未初始化。

**来源：** 卡码笔记 C++ enable_shared_from_this 专题 / Effective Modern C++ Item 19

## Explanation

正确答案是 C。
std::shared_ptr<Bad>(this) 创建了一个全新的控制块，不知道 sp1 已经有一个；析构时两个控制块都会 delete 同一个 this 指针 → double free。
正确用法： enable_shared_from_this 内部有一个 weak_ptr<T>，当对象首次被 shared_ptr 管理时，这个 weak_ptr 被初始化；shared_from_this() 通过 weak_ptr.lock() 返回与原 shared_ptr 共享控制块的新 shared_ptr。
注意：在构造函数中调用 shared_from_this() 会抛 bad_weak_ptr，因为此时 weak_ptr 还未初始化。
