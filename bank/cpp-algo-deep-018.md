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

---

**解析：**

- `std::sort`：O(n log n) 期望，**不保证稳定**——同分学生顺序可能错乱
- `std::stable_sort`：O(n log n) 或 O(n log² n)（取决于内存），**保证稳定**
- B 缺少比较器且 `Student` 没有 `operator<`，编译错误
- D `partial_sort` 用于"取前 k 个"语义不同

按多关键字"二轮排序"需要稳定排序：先按次关键字 stable_sort，再按主关键字 stable_sort，最终结果按主关键字升序、相等者按次关键字保序。
