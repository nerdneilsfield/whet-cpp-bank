---
qid: cpp-algo-deep-018
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: C
---

下列代码用 `std::stable_sort` 对学生按分数降序排序，相同分数保持原顺序，哪项**正确**？

```cpp
struct Student { std::string name; int score; };
std::vector<Student> v = {{"A",90},{"B",80},{"C",90},{"D",80}};
???
```

A. `std::sort(v.begin(), v.end(), [](auto& x, auto& y){return x.score > y.score;});`
B. `std::stable_sort(v.begin(), v.end());`
C. `std::stable_sort(v.begin(), v.end(), [](auto& x, auto& y){return x.score > y.score;});`
D. `std::partial_sort(v.begin(), v.end(), v.end(), [](auto& x, auto& y){return x.score > y.score;});`

## Explanation

正确答案是 C：要按分数降序且同分保持原相对顺序，必须用 stable_sort 并传 score > 的比较器。sort 不保证稳定，B 缺少 Student 的默认小于比较，D 的 partial_sort 不是为稳定排序设计。关键误区是把“排好序”和“稳定排序”混为一谈。
