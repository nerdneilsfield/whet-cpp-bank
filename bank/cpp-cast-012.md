---
qid: cpp-cast-012
type: fill
kp: [cpp-casting]
difficulty: easy
answer_key: "未定义行为（修改实际为 const 的对象）"
---

# const_cast 修改原 const 变量

```cpp
const int ci = 10;
int* p = const_cast<int*>(&ci);
*p = 20;  // 此行
std::cout << ci;
```

执行 "此行" 属于什么行为？___
