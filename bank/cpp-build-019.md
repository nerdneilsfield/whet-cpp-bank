---
qid: cpp-build-019
type: single
kp: [cpp-build-tools]
difficulty: easy
answer_key: B
---

# Makefile 规则中，recipe（配方）行必须以什么字符开头？

A. 空格  
B. Tab  
C. 井号 `#`  
D. 反斜杠 `\`

## 解析

正确答案是 B。Makefile 的 recipe 行传统上必须以 Tab 字符开头，普通空格不会被识别为命令前缀，常导致 “missing separator” 错误。较新的 GNU make 可用 `.RECIPEPREFIX` 改变前缀，但默认规则仍是 Tab。
