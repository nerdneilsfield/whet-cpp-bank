---
qid: cpp-taste-algo-010
type: single
kp: [cpp-algorithms, cpp-iterators, cpp-stl-basics]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: A
tags: [code-taste, best-practice]
---

要从 source vector 中拷贝前 N 个元素到 target。下面四个写法功能相同，哪个最有 C++ 味？

```cpp
// A
std::vector<int> src{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
const int N = 3;
std::vector<int> dst;
std::copy_n(src.begin(), N, std::back_inserter(dst));

// B
std::vector<int> src{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
const int N = 3;
std::vector<int> dst(src.begin(), src.begin() + N);

// C
std::vector<int> src{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
const int N = 3;
std::vector<int> dst;
for (int i = 0; i < N && i < (int)src.size(); ++i) {
    dst.push_back(src[i]);
}

// D
std::vector<int> src{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
const int N = 3;
std::vector<int> dst(N);
std::memcpy(dst.data(), src.data(), N * sizeof(int));
```

A. A — copy_n，名字就是"拷贝 N 个"

B. B — 范围构造，最简洁且安全

C. C — for 循环 + push_back，控制力最强

D. D — memcpy，零类型检查最快

---

**解析：**

选 A。虽然 B 在代码量上更短，但 `copy_n` 这个名字精确地表达了"拷贝 N 个"这个意图——**不需要读者知道迭代器算术**。

逐一品味为什么其他版本不好：

- **B**：`src.begin() + N` 依赖随机访问迭代器。如果 `src` 换成 `std::list`，`src.begin() + N` 编译不过。而 `copy_n` 只要求输入迭代器，不管底层容器是什么都能工作。更隐蔽的问题是：如果 N 大于 `src.size()`，`src.begin() + N` 是**未定义行为**。

- **C**：for 循环 + push_back，把 STL 已经封装好的事情重新发明了一遍。循环边界条件 `i < N && i < (int)src.size()` 还要处理类型转换，脆弱且混乱。

- **D**：`memcpy` 仅对 trivially copyable 类型有效（本题恰好是 int，可以工作）。一旦元素类型变成 `std::string` 或其他非平凡类型，`memcpy` 会破坏对象生命周期（不调用构造函数/析构函数）。而且 `dst.data()` 必须在 `resize(N)` 之后才有效——这里是 `vector<int> dst(N)` 的构造函数已经做了这件事，但读者要检查两行代码才能确认安全。

`copy_n` 在 C++11 加入，填补了一个明显的空缺：C++98 有 `copy`（范围→范围）但没有"拷贝前 N 个"。`copy_n` 接受一个起始迭代器和一个计数，对任何输入迭代器类型有效，且自动处理 N > size 的情况（不过标准要求 N 不超过范围长度，实际上仍由调用者保证）。

核心识别点：
- "拷贝前 N 个" → `copy_n`
- "拷贝整个范围" → `copy` 或范围构造
- "跳过前 N 个再拷贝" → `copy` + 迭代器偏移
- 不要写手写循环替代 `copy_n`
- 不要用 `memcpy`——它绕过了抽象层和生命周期