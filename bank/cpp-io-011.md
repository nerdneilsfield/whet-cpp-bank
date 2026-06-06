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
