---
qid: cpp-real-nk-017
type: single
kp: [cpp-memory-mgmt]
primary_kp: cpp-memory-mgmt
difficulty: medium
answer_key: A
tags: [interview-real, nowcoder]
---

```cpp
void foo() {
    std::unique_ptr<int> up(new int(42));
    // ...
}
```

`unique_ptr` 对象 `up` 本身和其管理的 `int(42)` 分别位于内存哪个区域？

A. `up` 在**栈**上，`int(42)` 在**堆**上
B. 都在堆上
C. 都在栈上
D. `up` 在堆上，`int(42)` 在栈上

---

**解析：**

智能指针是普通对象，遵循 C++ 对象的存储期规则：
- `up` 作为函数局部变量，存储在**栈**（自动存储期）
- `int(42)` 通过 `new` 分配，存储在**堆**（动态存储期）

unique_ptr 的核心机制就是利用 RAII：栈上对象的析构函数自动执行，析构函数中调用 delete 释放堆内存。

如果 unique_ptr 本身也在堆上（如 `new unique_ptr<int>(...)`），就需要手动 delete 这个 unique_ptr，违背了 RAII 初衷。

shared_ptr 同理：智能指针对象的存储位置由声明位置决定（栈/堆/全局），被管理对象通常在堆上（除非使用 `make_shared`，则对象与控制块同块堆内存）。

**来源：** 卡码笔记 C++ 智能指针专题 / huihut/interview

## Explanation

正确答案是 A。
智能指针是普通对象，遵循 C++ 对象的存储期规则： up 作为函数局部变量，存储在栈（自动存储期） int(42) 通过 new 分配，存储在堆（动态存储期） unique_ptr 的核心机制就是利用 RAII：栈上对象的析构函数自动执行，析构函数中调用 delete 释放堆内存。
如果 unique_ptr 本身也在堆上（如 new unique_ptr<int>(...)），就需要手动 delete 这个 unique_ptr，违背了 RAII 初衷。
shared_ptr 同理：智能指针对象的存储位置由声明位置决定（栈/堆/全局），被管理对象通常在堆上（除非使用 make_shared，则对象与控制块同块堆内存）。
