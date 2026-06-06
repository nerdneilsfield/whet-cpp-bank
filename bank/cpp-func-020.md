---
qid: cpp-func-020
type: single
kp: [cpp-functions]
difficulty: easy
answer_key: C
---

以下代码输出什么？

```cpp
int f(int x, int y = 10) { return x + y; }
int main() {
    std::cout << f(3) << " " << f(3, 4);
}
```

A. `3 7`
B. `10 4`
C. `13 7`
D. 编译错误
