---
qid: cpp-build-018
type: single
kp: [cpp-build-tools]
difficulty: easy
answer_key: D
---

# 题目

下面这条命令的含义是什么？
```
g++ -std=c++17 -O2 -Wall -Werror -Iinclude -o app main.cpp util.cpp -Llib -lmyutil
```

A. 用 C++14 标准，最低优化，编译 main.cpp，输出为 util.cpp
B. 只做预处理，不链接，输出 app.i
C. 以 C++17 标准、最高优化级别编译，关闭所有警告
D. 以 C++17 标准、`-O2` 优化，开启常见警告并将警告视为错误，从 `include/` 找头文件，链接 `lib/` 下的 `libmyutil`，输出可执行文件 `app`

## Explanation

- A：标准是 c++17 不是 c++14；`-O2` 也非最低优化。
- B：无 `-E` 选项，不会停在预处理。
- C：`-Wall -Werror` 是开启警告并把警告当错误，不是关闭警告；`-O2` 也不是最高级别（最高是 `-O3`）。
- D：正确。每个选项均有对应作用：`-std=c++17` 指定标准，`-O2` 中等优化，`-Wall -Werror` 严格警告，`-Iinclude` 头文件路径，`-o app` 输出名，`-Llib -lmyutil` 链接库。


正确答案为 D，因为“以 C++17 标准、`-O2` 优化，开启常见警告并将警告视为错误，从 `include/` 找头文件，链接 `lib/` 下的 `libmyutil`，输出可执行文件 `app`”符合题干所问的 C++ 规则或代码执行结果。A、B、C 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。构建题要区分预处理、编译、汇编、链接以及编译选项、库路径和目标文件的职责。
