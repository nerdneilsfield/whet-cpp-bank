---
qid: cpp-lambda-015
type: single
kp: [cpp-lambdas]
difficulty: easy
answer_key: B
---

# std::sort 自定义比较器

```cpp
std::vector<int> v = {3, 1, 4, 1, 5, 9};
std::sort(v.begin(), v.end(), [](int a, int b) {
    return a > b;
});
```

排序后 `v[0]` 的值是？

A. 1
B. 9
C. 3
D. 5
