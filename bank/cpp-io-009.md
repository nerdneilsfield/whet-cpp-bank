---
qid: cpp-io-009
type: fill
kp: [cpp-io]
difficulty: easy
answer_key: "is_open"
---

# 代码阅读：检查文件打开

```cpp
std::ifstream fin("data.txt");
if (!fin.______()) {
    std::cerr << "无法打开文件\n";
    return 1;
}
```

空格处应填写的函数名是 ______。

## 解析

应填写 `is_open`。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。该答案能与题干中的代码上下文、声明形式或输出结果精确匹配，因此既要关注语法位置，也要关注类型和值的含义。常见误区是写出近似形式但改变了指针/引用/捕获/格式化等语义，导致编译失败或结果不同。
