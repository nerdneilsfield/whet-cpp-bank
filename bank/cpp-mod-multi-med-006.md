---
qid: cpp-mod-multi-med-006
type: multi
kp: [cpp-cpp14-17]
difficulty: medium
answer_key: [A, B, D]
---
关于 `std::string_view` 的使用陷阱，**哪些说法是正确的**？（多选）

```cpp
std::string_view bad() {
    std::string s = "hello";
    return s;          // (1)
}
std::string_view sv = std::string("temp") + "x";  // (2)
const char* p = sv.data();  // (3)
```

A. (1) 返回的 `string_view` 指向已析构的 `s`，是悬空视图，使用是未定义行为
B. (2) 表达式右侧是临时对象，`sv` 绑定后临时对象立即销毁，`sv` 立即悬空
C. `string_view` 拥有所指字符的生命周期，类似 `shared_ptr` 的共享所有权
D. `string_view::data()` 返回的指针**不保证**以 `\0` 结尾，不能直接传给期望 C 风格字符串的 API

---

**解析：**

A 正确：`string_view` 是非所有者视图，`s` 离开作用域后视图悬空，访问是 UB。
B 正确：`string_view` 不会延长临时对象生命周期，临时 `std::string` 在表达式结束时销毁，`sv` 即刻悬空。
C 错误：`string_view` 是**非拥有**的（non-owning），只持有指针和长度，调用方需自行保证底层数据存活，这正是其主要使用陷阱。
D 正确：`string_view` 表示的可能是某个更长字符串的子串，`data()` 后没有保证的 `'\0'`。需要 C 字符串时必须先拷贝到 `std::string`。

## Explanation

正确答案是 [A, B, D]。A 正确：`string_view` 是非所有者视图，`s` 离开作用域后视图悬空，访问是 UB。
B 正确：`string_view` 不会延长临时对象生命周期，临时 `std::string` 在表达式结束时销毁，`sv` 即刻悬空。
C 错误：`string_view` 是非拥有的（non-owning），只持有指针和长度，调用方需自行保证底层数据存活，这正是其主要使用陷阱。
