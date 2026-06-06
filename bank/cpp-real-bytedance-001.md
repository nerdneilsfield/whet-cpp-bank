---
qid: cpp-real-bytedance-001
type: single
kp: [cpp-memory-mgmt, cpp-cpp11]
primary_kp: cpp-cpp11
difficulty: medium
answer_key: C
tags: [interview-real, bytedance]
---
```cpp
// C++98 风格
std::auto_ptr<int> p1(new int(42));
std::auto_ptr<int> p2 = p1;   // p1 被"偷走"，变为 nullptr

// C++11 风格
std::unique_ptr<int> u1(new int(42));
// std::unique_ptr<int> u2 = u1;  // 编译错误！
std::unique_ptr<int> u2 = std::move(u1);  // OK
```
关于 `auto_ptr` 在 C++11 中被弃用（C++17 删除）的根本原因，以下说法正确的是：

A. auto_ptr 不支持数组，所以被淘汰
B. auto_ptr 占用空间太大，性能差
C. auto_ptr 的拷贝构造实际上是**所有权转移**（"偷"），但语法上看起来像普通拷贝，容易误用——尤其在 STL 容器中使用时元素被复制后原对象被清空，行为非常违反直觉
D. auto_ptr 不支持自定义 deleter

---

**解析：**

选 C。auto_ptr 是 C++98 唯一的智能指针，但有几个**致命缺陷**：

**1. 拷贝即转移（最大问题）：**
```cpp
auto_ptr<int> p1(new int(42));
auto_ptr<int> p2 = p1;   // 看起来是拷贝，实际 p1 被设为 nullptr
*p1;  // UB! 解引用 nullptr
```
这违反了"拷贝构造后两个对象等价"的常识，极易导致 bug。

**2. 不能放入 STL 容器：**
STL 容器（vector、list 等）要求元素**可拷贝**（CopyConstructible）且**拷贝后内容相等**。auto_ptr 的"伪拷贝"会破坏容器：
```cpp
std::vector<auto_ptr<int>> v;
v.push_back(auto_ptr<int>(new int(1)));
auto_ptr<int> x = v[0];  // v[0] 被清空！
```

**3. C++11 引入 unique_ptr 完美解决：**
- 删除拷贝构造（`= delete`），只允许移动
- 必须显式 `std::move` 才能转移所有权
- 编译期防止误用
- 支持自定义 deleter、数组特化（`unique_ptr<T[]>`）

**结论：** auto_ptr 在 C++11 被 [[deprecated]]，C++17 正式删除。所有新代码都应该用 unique_ptr / shared_ptr。

A 错，是缺点之一但不是根本。B 错，auto_ptr 只有一个指针大小。D 错，定制 deleter 是次要因素。

**来源：** 字节 C++ 面试常考（参考：Effective Modern C++ Item 18、cppreference）

## Explanation

正确答案是 C。
A 错，是缺点之一但不是根本；B 错，auto_ptr 只有一个指针大小。
D 错，定制 deleter 是次要因素。
