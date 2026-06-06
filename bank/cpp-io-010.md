---
qid: cpp-io-010
type: fill
kp: [cpp-io]
difficulty: easy
answer_key: "hello world"
---

# 代码阅读：逐行读取输出

文件 `test.txt` 内容：
```
hello world
foo bar
```

```cpp
std::ifstream fin("test.txt");
std::string line;
std::getline(fin, line);
std::cout << line;
```

程序输出是 ______。
