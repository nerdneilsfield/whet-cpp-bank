---
qid: cpp-cpp17-019
type: multi
kp: [cpp-cpp14-17]
difficulty: easy
answer_key: [A, C, D]
---

# 代码阅读：std::string_view 的合法用法

下列关于 `std::string_view` 的用法，哪些是正确/安全的？（多选）

```cpp
// 选项 A
std::string s = "hello";
std::string_view sv = s;          // 从 std::string 构造

// 选项 B
std::string_view get_view() {
    std::string local = "temp";
    return local;                  // 返回对局部变量的视图
}

// 选项 C
void print(std::string_view sv) {
    std::cout << sv << "\n";       // 传参接受 string 和字面量
}

// 选项 D
std::string_view sv2 = "literal"; // 从字符串字面量构造
```

A. 选项 A 安全：`sv` 引用 `s` 的数据，`s` 的生命周期覆盖 `sv`
B. 选项 B 安全：`string_view` 会复制字符串内容
C. 选项 C 正确：`print` 可以接受 `std::string`、`const char*` 和字面量
D. 选项 D 安全：字符串字面量有静态存储期

## Explanation

正确答案是 A、C、D。`std::string_view` 是非拥有视图，只保存指针和长度，必须注意底层字符序列生命周期。 A 正确：选项 A 安全：｀sv｀ 引用 ｀s｀ 的数据，｀s｀ 的生命周期覆盖 ｀sv｀；B 错误：选项 B 安全：｀string_view｀ 会复制字符串内容；C 正确：选项 C 正确：｀print｀ 可以接受 ｀std::string｀、｀const char*｀ 和字面量；D 正确：选项 D 安全：字符串字面量有静态存储期。常见误区是只记住术语名称，而忽略每个选项中的限定条件、生命周期、同步关系或复杂度前提。
