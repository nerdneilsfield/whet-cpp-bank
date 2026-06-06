---
qid: cpp-io-016
type: single
kp: [cpp-io]
difficulty: easy
answer_key: C
---

# 代码阅读：追加写入模式

```cpp
std::ofstream fout("log.txt", std::ios::app);
fout << "新记录\n";
```

执行后 `log.txt` 的状态是：

A. 文件被清空，只含 `新记录\n`
B. 文件打开失败（`ios::app` 不能与 `ofstream` 同用）
C. 原有内容保留，`新记录\n` 追加在末尾
D. 文件以只读方式打开，写入被忽略

## Explanation

正确答案是 C，对应“原有内容保留，新记录\n 追加在末尾”。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。其他选项容易混淆相关概念：A 项“文件被清空，只含 新记录\n”不满足题干要求；B 项“文件打开失败（ios::app 不能与 ofstream 同用）”不满足题干要求；D 项“文件以只读方式打开，写入被忽略”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
