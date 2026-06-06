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
