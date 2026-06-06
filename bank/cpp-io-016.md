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
