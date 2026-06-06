---
qid: cpp-ub-020
type: multi
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: [B, C]
---

# 综合判断：以下哪些代码片段存在 UB（多选）

```cpp
// 片段 A
unsigned int x = UINT_MAX;
x += 1;   // x 变为 0

// 片段 B
int arr[4];
int v = arr[4];   // 下标 4，越界

// 片段 C
char* p = new char[8];
delete[] p;
p[0] = 'x';   // use-after-free

// 片段 D
int n;
std::cin >> n;
int result = n * 2;   // n 已初始化，来自 cin
```

哪些片段存在未定义行为？（多选）

A. 片段 A
B. 片段 B
C. 片段 C
D. 片段 D
