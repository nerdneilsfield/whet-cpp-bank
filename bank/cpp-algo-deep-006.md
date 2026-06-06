---
qid: cpp-algo-deep-006
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: C
---

下列代码用 `std::replace_if` 把所有偶数替换为 0，正确写法是？

```cpp
std::vector<int> v{1,2,3,4,5,6};
???
// 期望结果：1 0 3 0 5 0
```

A. `std::replace_if(v.begin(), v.end(), [](int x){return x%2==0;});`
B. `std::replace_if(v.begin(), v.end(), 0, [](int x){return x%2==0;});`
C. `std::replace_if(v.begin(), v.end(), [](int x){return x%2==0;}, 0);`
D. `std::replace(v.begin(), v.end(), [](int x){return x%2==0;}, 0);`

---

**解析：**

`std::replace_if` 的签名是 `replace_if(first, last, pred, new_value)`：先是谓词，最后是新值。`std::replace` 的签名是 `replace(first, last, old_value, new_value)`，要求 `==` 比较；它不接受谓词。

记忆口诀：带 `_if` 的算法把"要比较的具体值"换成"谓词"，且谓词位置与对应的"值参数"位置相同。
