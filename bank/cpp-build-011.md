---
qid: cpp-build-011
type: fill
kp: [cpp-build-tools]
difficulty: easy
answer_key: -L./lib -lmyutil
---

# 题目

共享库 `libmyutil.so` 放在 `./lib` 目录中。链接时需要同时使用两个选项：用 **___** 指定库的搜索目录，用 **___** 指定库名（合并写法：**___**）。

## 答案

`-L./lib`（添加库搜索路径）和 `-lmyutil`（链接 libmyutil），合并写法为 `-L./lib -lmyutil`。注意 `-l` 后面的名称去掉 `lib` 前缀和 `.so` 后缀。
