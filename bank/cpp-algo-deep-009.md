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

---

**解析：**

`vector::erase(it)` 让 `it` 指向**被删元素的下一个**，紧接的 `++it` 又跳过一格，导致原本紧跟在被删偶数后的偶数被漏掉。例如删 2 后 it 指向 3，再 ++ 指向 4 时，4 没被检查到的位置错位。

正确写法：使用返回值控制迭代器：

```cpp
for (auto it = v.begin(); it != v.end(); ) {
    if (*it % 2 == 0) it = v.erase(it);
    else ++it;
}
// 或直接：
v.erase(std::remove_if(v.begin(), v.end(),
        [](int x){return x%2==0;}), v.end());
// C++20:
std::erase_if(v, [](int x){return x%2==0;});
```
