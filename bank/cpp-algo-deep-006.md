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

## Explanation

正确答案是 C：std::replace_if 的参数顺序是 first, last, pred, new_value，所以谓词在第三个位置，新值在第四个位置。std::replace 则按旧值做相等比较，不接受谓词。常见误区是把 replace 与 replace_if 的参数形状混用。
