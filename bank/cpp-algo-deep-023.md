---
qid: cpp-algo-deep-023
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: B
---

下列代码输出是？

```cpp
std::vector<int> v{1,3,5,7,4,9,11};
auto it = std::is_sorted_until(v.begin(), v.end());
std::cout << (it - v.begin()) << " " << *it;
```

A. `0 1`
B. `4 4`（前 4 个有序，下标 4 处的 4 破坏顺序）
C. `7` （整个向量长度）
D. `3 7`

## Explanation

正确答案是 B：is_sorted_until 返回第一个破坏升序的位置。1,3,5,7 是有序前缀，后面的 4 小于前一个 7，因此返回下标 4，解引用为 4。若整个范围都有序才会返回 end，所以实际代码中不能在未检查时无条件解引用，否则可能越界。
