---
qid: cpp-algo-med-003
type: single
kp: [cpp-algorithms]
difficulty: medium
answer_key: B
---

下列代码会发生什么？

```cpp
std::list<int> lst = {3, 1, 4, 1, 5, 9, 2, 6};
std::sort(lst.begin(), lst.end());
```

A. 编译通过、运行正确，`lst` 被排序为 `{1,1,2,3,4,5,6,9}`
B. 编译失败：`std::sort` 要求 random-access iterator，而 `list::iterator` 是 bidirectional
C. 编译通过但运行抛 `std::logic_error`：标准库检测到迭代器分类不匹配
D. 编译通过但是 O(n²) 慢排，因为 `list` 节点散落

---

**解析：**

`std::sort` 在标准上要求传入 **random-access iterator**（[alg.sort]）——它的实现通常是 introsort（quicksort + heapsort 切换），需要 `it + n`、`it1 - it2` 之类的常数时间操作，否则算法的 O(n log n) 复杂度保证不成立。

`std::list::iterator` 是 bidirectional iterator，没有 `+ n` 和 `-` 运算符。把它传给 `std::sort` 在 SFINAE/concept 阶段就会失败——C++20 起 `std::sortable` concept 直接拒绝，C++17 及之前则在模板实例化深处报一长串编译错误，但都是**编译期失败**，不会走到运行期。

`std::list` 自带成员函数 `lst.sort()`，专为链表写：节点不动，只重连指针，复杂度 O(n log n)，原地稳定。`std::forward_list` 也有 `sort()` 成员。

这条规则是 STL 算法/容器接口契约的范例：算法对迭代器能力分类有显式要求，容器把自己最适合的操作放在成员函数里，两者职责互不重叠。

## 解析

正确答案为 B，因为“编译失败：`std::sort` 要求 random-access iterator，而 `list::iterator` 是 bidirectional”符合题干所问的 C++ 规则或代码执行结果。A、C、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。STL 算法通常只操作迭代器区间，前置条件、返回值和是否改变容器大小要分开判断。
