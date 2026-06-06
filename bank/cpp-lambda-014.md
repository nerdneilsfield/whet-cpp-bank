---
qid: cpp-lambda-014
type: fill
kp: [cpp-lambdas]
difficulty: easy
answer_key: "6"
---

# 立即调用 lambda

```cpp
int result = [](int a, int b) { return a * b; }(2, 3);
std::cout << result;
```

程序输出为：___

## 解析

应填写 `6`。本题考查 lambda 的捕获方式、调用对象和可变性，关键是区分按值捕获、按引用捕获以及闭包对象保存状态的规则。该答案能与题干中的代码上下文、声明形式或输出结果精确匹配，因此既要关注语法位置，也要关注类型和值的含义。常见误区是写出近似形式但改变了指针/引用/捕获/格式化等语义，导致编译失败或结果不同。
