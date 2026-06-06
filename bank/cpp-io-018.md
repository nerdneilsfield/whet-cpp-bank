---
qid: cpp-io-018
type: multi
kp: [cpp-io]
difficulty: easy
answer_key: [A, C, D]
---

# 代码阅读：逐行读取文件所有行

以下哪些代码片段能**正确**逐行读取文件 `in.txt` 的所有行并打印？（多选）

A.
```cpp
std::ifstream f("in.txt");
std::string line;
while (std::getline(f, line))
    std::cout << line << '\n';
```

B.
```cpp
std::ifstream f("in.txt");
std::string line;
while (f >> line)
    std::cout << line << '\n';  // 注：逐词不逐行
```

C.
```cpp
std::ifstream f("in.txt");
for (std::string line; std::getline(f, line); )
    std::cout << line << '\n';
```

D.
```cpp
std::ifstream f("in.txt");
std::string line;
while (!f.eof()) {
    std::getline(f, line);
    if (f)  // 成功才打印
        std::cout << line << '\n';
}
```

E.
```cpp
std::ifstream f("in.txt");
std::string all((std::istreambuf_iterator<char>(f)),
                 std::istreambuf_iterator<char>());
std::cout << all;  // 一次性读全文，非逐行
```

> B 逐词非逐行，E 非逐行，均不符合题意。

## 解析

本题正确答案是 A, C, D。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。A 项正确：“cpp std::ifstream f("in.txt"); std::string line; while (std::getline(f, line)) std::cout << line << '\n'; ”符合题干要求；B 项错误：“cpp std::ifstream f("in.txt"); std::string line; while (f >> line) std::cout << line << '\n'; // 注：逐词不逐行 ”与题干要求或 C++ 规则不符；C 项正确：“cpp std::ifstream f("in.txt"); for (std::string line; std::getline(f, line); ) std::cout << line << '\n'; ”符合题干要求；D 项正确：“cpp std::ifstream f("in.txt"); std::string line; while (!f.eof()) { std::getline(f, line); if (f) // 成功才打印 std::cout << line << '\n'; } ”符合题干要求。多选题常见误区是漏选同时成立的规则，或把只在特定上下文成立的说法当成普遍规则。
