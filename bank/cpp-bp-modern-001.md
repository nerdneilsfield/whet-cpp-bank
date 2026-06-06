---
qid: cpp-bp-modern-001
type: single
kp: [cpp-cpp14-17]
difficulty: medium
answer_key: B
---

下列哪个函数签名最适合"可能找不到的查询"操作？

```cpp
class UserDB {
public:
    // A
    User find_by_id(int id);          // 找不到时？

    // B
    std::optional<User> find_by_id(int id);

    // C
    bool find_by_id(int id, User* out);

    // D
    User* find_by_id(int id);         // 找不到返回 nullptr？

    // E
    User find_by_id_or_throw(int id); // 抛异常
};
```

A. A
B. B：std::optional 最现代，无堆分配，显式表达"可能没有"
C. C
D. D

---

## Explanation

`std::optional<T>` （C++17）是表达"可能不存在的值"的现代方式。设计取向比较：

- **A 哑值**：`find_by_id` 找不到时返回什么？默认构造的 User？空字符串？任何 sentinel 都需要文档说明，调用方容易遗漏
- **B optional**：表意最明确，无堆分配（栈上 sizeof(T) + 1 字节 bool），强迫调用方处理两种情况
- **C 输出参数**：丑、易错（out 必须非空）、不支持链式调用、不支持 RVO
- **D 裸指针**：调用方误把它当做"我拥有这块内存"，企图 `delete`；语义不清（findable 还是 owned？）
- **E 异常**：找不到是常规情况，用异常成本太高且语义不对（"用户不存在"不是"异常"）

**std::optional 标准用法：**

```cpp
auto user = db.find_by_id(42);
if (user) {
    std::cout << user->name;
}

// 或链式
if (auto u = db.find_by_id(42); u && u->active) {
    process(*u);
}

// 默认值
std::string name = db.find_by_id(42)
    .transform([](const User& u) { return u.name; })  // C++23
    .value_or("Anonymous");
```

注意陷阱：
1. `optional<reference_wrapper<T>>`：optional 不能直接持有引用，用 reference_wrapper 包装
2. `optional<bool>` 有歧义：三态值（nullopt/false/true），需小心
3. `optional<T>` 存储 sizeof(T) + 1 字节（对齐后通常 +alignment），不是免费
4. `optional` 的 `*` 解引用不检查，无值时是 UB；用 `.value()` 抛异常

正确答案 B。这是 C++17 改变 API 设计实践的最重要特性之一。
