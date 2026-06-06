---
qid: cpp-types-025
type: fill
kp: [cpp-types]
difficulty: easy
answer_key: "constexpr"
---
若要声明一个**编译期常量**，使其可以用作数组大小或模板参数，应使用哪个关键字？

```cpp
___ int MAX = 100;
int arr[MAX]; // 合法
```

填入关键字：___

## Explanation

填入 `constexpr`，因为题目要求的是该规则下的精确表达或标准名称。指针、数组和引用题要注意数组到指针退化、指针算术按元素大小推进，以及引用绑定后只是对象别名。 常见误区是写出近似说法、旧式写法或省略必要的命名空间/符号，导致与答案含义不完全一致。
