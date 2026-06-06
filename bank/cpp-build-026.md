---
qid: cpp-build-026
type: fill
kp: [cpp-build-tools]
difficulty: easy
answer_key: "ar rcs libfoo.a foo.o"
---

# 在 Makefile 中，将目标文件 `foo.o` 打包成静态库 `libfoo.a` 的命令是：

`____`

## Explanation

答案是 `ar rcs libfoo.a foo.o`。`ar` 用于创建和维护静态库归档文件，`r` 表示插入/替换成员，`c` 表示创建库，`s` 生成索引。生成的 `libfoo.a` 可在链接时用 `-L` 和 `-lfoo` 使用。
