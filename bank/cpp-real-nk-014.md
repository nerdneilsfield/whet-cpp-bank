---
qid: cpp-real-nk-014
type: single
kp: [cpp-memory-mgmt]
primary_kp: cpp-memory-mgmt
difficulty: medium
answer_key: A
tags: [interview-real, nowcoder]
---

```cpp
std::weak_ptr<int> wp;
{
    auto sp = std::make_shared<int>(42);
    wp = sp;
}
auto sp2 = wp.lock();
if (sp2) {
    std::cout << *sp2;
} else {
    std::cout << "expired";
}
```

输出是：

A. `expired`

B. `42`

C. 段错误

D. 未定义行为

---

**解析：**

`weak_ptr::lock()` 返回一个 `shared_ptr`：

- 如果原对象还存在：lock() 增加引用计数并返回有效 shared_ptr
- 如果对象已释放：返回**空的 shared_ptr**（相当于 default constructed），不会产生未定义行为

本题中 sp 离开作用域后对象被释放，wp.expired() 为 true，lock() 返回空。访问空 shared_ptr 不会崩溃（operator bool 返回 false）。

对比：如果直接用 `weak_ptr::expired()` 判断后再 `lock()`，存在竞态条件（函数间可能释放），正确用法是直接 lock() 并判断 bool。

**来源：** 卡码笔记 C++ 智能指针面试题 / cppreference

## Explanation

正确答案是 A。
对比：如果直接用 weak_ptr::expired() 判断后再 lock()，存在竞态条件（函数间可能释放），正确用法是直接 lock() 并判断 bool。
weak_ptr::lock() 返回一个 shared_ptr： 如果原对象还存在：lock() 增加引用计数并返回有效 shared_ptr 如果对象已释放：返回空的 shared_ptr（相当于 default constructed），不会产生未定义行为 本题中 sp 离开作用域后对象被释放，wp.expired() 为 true，lock() 返回空。访问空 shared_ptr 不会崩溃（operator bool 返回 false）。
