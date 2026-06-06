---
qid: cpp-mod-multi-med-001
type: multi
kp: [cpp-cpp11]
difficulty: medium
answer_key: [A, C]
---
关于以下 `auto` 类型推导，**哪些说法是正确的**？（多选）

```cpp
const int  ci = 42;
const int& cr = ci;
int arr[3] = {1, 2, 3};

auto a = ci;        // (1)
auto b = cr;        // (2)
auto c = arr;       // (3)
auto d = {1, 2, 3}; // (4)
```

A. (1) 中 `a` 的类型是 `int`，顶层 `const` 被丢弃
B. (2) 中 `b` 的类型是 `const int&`，引用和 `const` 都被保留
C. (3) 中 `c` 的类型是 `int*`，数组退化为指针
D. (4) 中 `d` 的类型是 `int[3]`，花括号被推导为数组

---

**解析：**

A 正确：`auto` 按值推导时会丢弃顶层 `const` 和引用，因此 `a` 是 `int`。
B 错误：`auto` 默认按值推导，引用被剥离、顶层 `const` 被丢弃，`b` 的类型是 `int`，不是 `const int&`。要保留需写 `auto&` 或 `decltype(auto)`。
C 正确：`auto`（非引用形式）触发数组到指针的退化，`c` 是 `int*`。若写 `auto&`，则推导为 `int(&)[3]`。
D 错误：`auto x = {...}` 这种**直接花括号初始化**会被特殊推导为 `std::initializer_list<int>`，而非数组。
