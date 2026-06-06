---
qid: cpp-cf-017
type: single
kp: [cpp-control-flow]
difficulty: easy
answer_key: C
---

以下嵌套循环共输出多少行 `"*"`？

```cpp
for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
        std::cout << "*\n";
    }
}
```

A. 3
B. 2
C. 6
D. 5
