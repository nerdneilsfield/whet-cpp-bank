---
qid: cpp-bp-perf-003
type: single
kp: [cpp-stl-basics]
difficulty: medium
answer_key: B
---

下面字符串拼接代码的性能问题分析：

```cpp
std::string greet(const std::string& name, const std::string& title) {
    return "Hello, " + title + " " + name + ", welcome!";
}
```

A. 无性能问题，编译器会优化
B. 中间会产生多个临时 std::string，每个都触发独立的堆分配
C. operator+ 会调用 memcpy，已经最快
D. 应该用 strcat

---

**解析：**

`std::string operator+` 是普通的二元运算符。表达式 `"Hello, " + title + " " + name + ", welcome!"` 等价于：

```
tmp1 = std::string("Hello, ") + title;   // 分配 1
tmp2 = tmp1 + " ";                        // 分配 2
tmp3 = tmp2 + name;                       // 分配 3
tmp4 = tmp3 + ", welcome!";               // 分配 4
return tmp4;
```

每个 `+` 都产生一个**新的临时 std::string**，每个都需要 malloc。即使有 SBO（small buffer optimization），超过约 15 字节后就一定 malloc。

更糟的是，每个临时 string 的容量都按"刚好够"分配，**重复 grow** 类似 vector 的扩容问题。

正确做法（按优先级）：

1. 用 `std::format`（C++20）—— 计算总长度后单次分配：
```cpp
return std::format("Hello, {} {}, welcome!", title, name);
```

2. 用 `+=` 或 `append` 串联到同一 string，先 reserve：
```cpp
std::string s;
s.reserve(name.size() + title.size() + 20);
s += "Hello, ";  s += title;  s += " ";  s += name;  s += ", welcome!";
return s;
```

3. 用 `std::ostringstream`（最慢但灵活）。

4. C++17 的 `string_view` + 内部 builder（如 absl::StrCat）。

注意：编译器通常**不能优化掉这些临时分配**，因为 `operator+` 是普通函数调用，无法跨调用合并分配。RVO 仅消除返回值拷贝，无法消除中间临时对象。