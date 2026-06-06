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

## 解析

正确选项是 B（片段 B）、C（片段 C），它们符合本题涉及的 C++ 规则。A（片段 A）、D（片段 D） 的关键问题在于混淆了相关概念或把实现细节当成语言保证。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 多选题要逐项判断，不能因为某个说法在常见平台上成立就认为它是标准规则。
