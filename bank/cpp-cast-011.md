---
qid: cpp-cast-011
type: fill
kp: [cpp-casting]
difficulty: easy
answer_key: "编译错误（不能用 static_cast 去除 const）"
---

# static_cast 去 const

```cpp
const int ci = 42;
int* p = static_cast<int*>(&ci);  // 此行
```

上述代码（"此行"）会发生什么？___
