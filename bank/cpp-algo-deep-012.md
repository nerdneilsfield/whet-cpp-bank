---
qid: cpp-algo-deep-012
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: C
---

对**空范围**调用，下列断言哪项**全部正确**？

```cpp
std::vector<int> v;  // 空
bool a = std::all_of (v.begin(), v.end(), [](int){return false;});
bool b = std::any_of (v.begin(), v.end(), [](int){return true;});
bool c = std::none_of(v.begin(), v.end(), [](int){return true;});
```

A. `a = false, b = true,  c = false`
B. `a = false, b = false, c = true`
C. `a = true,  b = false, c = true`
D. `a = true,  b = true,  c = true`

## Explanation

正确答案是 C：空范围上 all_of 返回 true，这是空真；any_of 返回 false，因为没有元素满足谓词。none_of 返回 true，因为没有元素违反条件。误区是把 all_of 为 true 理解为“至少有一个且全满足”，实际还需单独检查非空。
