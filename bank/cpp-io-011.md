---
qid: cpp-io-011
type: fill
kp: [cpp-io]
difficulty: easy
answer_key: "3"
---

# 代码阅读：逐词计数

文件 `words.txt` 内容：`apple banana cherry`（单行，三个词）

```cpp
std::ifstream fin("words.txt");
std::string word;
int count = 0;
while (fin >> word) ++count;
std::cout << count;
```

程序输出是 ______。

## Explanation

应填写 `3`。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。该答案能与题干中的代码上下文、声明形式或输出结果精确匹配，因此既要关注语法位置，也要关注类型和值的含义。常见误区是写出近似形式但改变了指针/引用/捕获/格式化等语义，导致编译失败或结果不同。
