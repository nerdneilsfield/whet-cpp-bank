---
qid: cpp-cont-019
type: multi
kp: [cpp-containers]
difficulty: easy
answer_key: [B, D]
---

阅读以下代码片段，哪些说法正确？（多选）

```cpp
std::map<int, std::string> m;
auto it1 = m.insert({1, "one"}).first;
auto it2 = m.insert({2, "two"}).first;
m.insert({3, "three"});
```

A. 插入 `{3,"three"}` 后，`it1` 和 `it2` 均失效
B. 插入后 `it1` 和 `it2` 依然有效
C. `m.insert({1,"one"})` 返回 `void`
D. `m.insert({1,"one"})` 返回 `std::pair<iterator, bool>`
