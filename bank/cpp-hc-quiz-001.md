---
qid: cpp-hc-quiz-001
type: single
kp: [cpp-cpp11, cpp-stl-basics]
primary_kp: cpp-cpp11
difficulty: hard
answer_key: B
tags: [interview-real, handcrafted, language-lawyer]
---
根据 C++17 标准，以下程序两行输出分别是什么？

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> a{3, 5};
    std::vector<int> b(3, 5);
    std::cout << a.size() << " " << a[0] << "\n";
    std::cout << b.size() << " " << b[0] << "\n";
}
```

A. `2 3` 和 `2 3`
B. `2 3` 和 `3 5`
C. `3 5` 和 `2 3`
D. 编译错误：`{3, 5}` 与 `(3, 5)` 都构造歧义

---

**解析：**

选 B。这是 `{}` vs `()` 在容器构造上**最常踩**的坑。

`std::vector<int>` 有两个相关构造函数：

1. `vector(size_type n, const T& value)` —— 构造 n 个 value
2. `vector(std::initializer_list<T>)` —— 用列表填充

**列表初始化的优先级规则（[over.match.list]）**：当用 `{...}` 时，**`initializer_list` 构造函数优先**——只要 braced-init-list 能匹配它，就选它，哪怕"显式构造函数"语义上更合理。

- `vector<int> a{3, 5};` → 选 `initializer_list<int>{3, 5}`，得到 `[3, 5]`，size=2、a[0]=3
- `vector<int> b(3, 5);` → 圆括号，直接初始化，选 `vector(3, 5)`，得到 `[5, 5, 5]`，size=3、b[0]=5

两种语法只差一对括号，**结果完全不同**。

这就是 Scott Meyers 在《Effective Modern C++》Item 7 "Distinguish between `()` and `{}`" 里专门告诫的陷阱：

> 在大多数情况下偏好 `{}`（防 narrowing、防 most vexing parse），但**对接受 size_type 的标准库容器要警惕**，因为 `initializer_list` 构造函数会"贪婪"地匹配。

类似的坑：
```cpp
std::vector<int> v1(10, 20);  // [20]*10
std::vector<int> v2{10, 20};  // [10, 20]

std::string s1(10, 'x');      // "xxxxxxxxxx"
std::string s2{10, 'x'};      // 两字符：'\n' 和 'x' (因为 10 是 char 范围内的 int)
```

记忆口诀：**`{}` 给 `initializer_list` 优先权——它能匹配就赢**。

C 和 A 是把两种结果搞反或一致化。D 错——两种语法都合法，没有歧义。

**来源：** 手写题。规则参见 ISO/IEC 14882:2017 §16.3.1.7 [over.match.list]；Scott Meyers, *Effective Modern C++*, Item 7。

## Explanation

正确答案是 B。这是 `{}` vs `()` 在容器构造上最常踩的坑。
这是 `{}` vs `()` 在容器构造上最常踩的坑。
D 错——两种语法都合法，没有歧义。
