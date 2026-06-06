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

## Explanation

正确答案是 B：std::search 用于在一个序列中查找另一个子序列，正适合查找字符串 pat。std::find 只能查找单个元素，不能把 string 当作 char 去找。find_if 只能找到任一出现在 pat 中的字符，adjacent_find 则查相邻关系，都不是子串匹配。
