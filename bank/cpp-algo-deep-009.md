---
qid: cpp-algo-deep-009
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: hard
answer_key: B
---

下列代码在容器上反向遍历删除偶数，行为是？

```cpp
std::vector<int> v{1,2,3,4,5,6};
for (auto it = v.begin(); it != v.end(); ++it) {
    if (*it % 2 == 0) v.erase(it);
}
```

A. 正确删除所有偶数
B. 跳过部分偶数（如 4 不会被删），因为 `erase` 使后续元素前移而 `++it` 又跳过
C. 编译错误
D. 删除后 `v` 变空

## Explanation

正确答案是 B：vector::erase 会使被删位置及其后的迭代器失效，并返回下一个有效迭代器。题中忽略返回值且循环末尾继续 ++it，会跳过元素，甚至有迭代器失效风险。正确写法是在删除时令 it = v.erase(it)，否则才 ++it，或直接用 erase-remove/erase_if。
