---
qid: cpp-build-024
type: single
kp: [cpp-build-tools]
difficulty: easy
answer_key: B
---

# 以下 Makefile 片段中，`.PHONY: clean` 的作用是什么？

```makefile
.PHONY: clean
clean:
    rm -f *.o app
```

A. 声明 `clean` 目标会生成名为 `clean` 的文件  
B. 声明 `clean` 是伪目标，即使存在名为 `clean` 的文件也强制执行其 recipe  
C. 阻止 `make clean` 被调用  
D. 将 `clean` 设为默认目标

## Explanation

正确答案为 B，因为“声明 `clean` 是伪目标，即使存在名为 `clean` 的文件也强制执行其 recipe”符合题干所问的 C++ 规则或代码执行结果。A、C、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。构建题要区分预处理、编译、汇编、链接以及编译选项、库路径和目标文件的职责。
