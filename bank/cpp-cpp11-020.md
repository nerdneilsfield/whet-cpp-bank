---
qid: cpp-cpp11-020
type: multi
kp: [cpp-cpp11]
difficulty: easy
answer_key: [A, B, D]
---

# 代码阅读：noexcept 与 = default 综合

阅读以下类定义，哪些说法**正确**？（多选）

```cpp
struct Tracker {
    Tracker() = default;
    Tracker(const Tracker&) = delete;
    Tracker(Tracker&&) noexcept = default;
    ~Tracker() = default;
};
```

A. `Tracker t;` 可以编译——默认构造函数由编译器生成
B. `Tracker a; Tracker b = std::move(a);` 可以编译——移动构造函数存在
C. `Tracker a; Tracker b = a;` 可以编译——拷贝可以退化为移动
D. 移动构造函数标记了 `noexcept`，可用于 `std::vector` 重新分配时的高效移动
E. `= default` 的析构函数会阻止编译器内联析构

## Explanation

正确答案是 A、B、D。`= delete` 明确禁用某个函数，误用会在编译期报错而不是运行期失败。 A 正确：｀Tracker t;｀ 可以编译——默认构造函数由编译器生成；B 正确：｀Tracker a; Tracker b = std::move(a);｀ 可以编译——移动构造函数存在；C 错误：｀Tracker a; Tracker b = a;｀ 可以编译——拷贝可以退化为移动；D 正确：移动构造函数标记了 ｀noexcept｀，可用于 ｀std::vector｀ 重新分配时的高效移动；E 错误：｀= default｀ 的析构函数会阻止编译器内联析构。常见误区是只记住术语名称，而忽略每个选项中的限定条件、生命周期、同步关系或复杂度前提。
