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
