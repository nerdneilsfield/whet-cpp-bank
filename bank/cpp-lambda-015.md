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

## Explanation

正确答案是 B，对应“9”。本题考查 lambda 的捕获方式、调用对象和可变性，关键是区分按值捕获、按引用捕获以及闭包对象保存状态的规则。其他选项容易混淆相关概念：A 项“1”不满足题干要求；C 项“3”不满足题干要求；D 项“5”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
