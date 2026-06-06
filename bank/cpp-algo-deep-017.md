---
qid: cpp-algo-deep-017
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: B
---

要在 `text` 中查找子串 `"abc"` 首次出现位置，下列哪个算法**正确且最合适**？

```cpp
std::string text = "xxabcyyabcz";
std::string pat  = "abc";
???
```

A. `std::find(text.begin(), text.end(), pat);`
B. `std::search(text.begin(), text.end(), pat.begin(), pat.end());`
C. `std::find_if(text.begin(), text.end(), [&](char c){return pat.find(c)!=std::string::npos;});`
D. `std::adjacent_find(text.begin(), text.end());`

---

**解析：**

`std::find` 查找**单个元素**，传入字符串会编译错误（`char` 不能与 `string` 比较）。`std::search(haystack_first, haystack_last, needle_first, needle_last)` 才是查找**子序列**的算法。

C++17 起 `std::search` 支持高级搜索器：`std::boyer_moore_searcher`、`std::boyer_moore_horspool_searcher` 等，可处理大文本：

```cpp
std::search(text.begin(), text.end(),
            std::boyer_moore_searcher(pat.begin(), pat.end()));
```

`std::string::find` 也是常用方案。`std::find_first_of` 是"找第一个出现在另一集合中的字符"，语义不同。
