---
qid: cpp-io-020
type: multi
kp: [cpp-io]
difficulty: easy
answer_key: [A, D]
---

# 代码阅读：cin.ignore() 修复残留换行

以下场景中，哪些情况**需要** `cin.ignore()` 来避免 `getline` 读到空行？（多选）

A.
```cpp
int n;
cin >> n;
// 此处需要 cin.ignore()
string line;
getline(cin, line);
```

B.
```cpp
string a, b;
getline(cin, a);
getline(cin, b);  // 上一次 getline 已消耗换行，无需 ignore
```

C.
```cpp
cin >> ws;  // ws 操纵符跳过前导空白含换行，已处理
string line;
getline(cin, line);
```

D.
```cpp
double x;
char ch;
cin >> x >> ch;
// ch 读完后缓冲区仍有 '\n'
string line;
getline(cin, line);  // 此处需要 ignore
```

E.
```cpp
// 程序刚启动，缓冲区为空，无需 ignore
string line;
getline(cin, line);
```
