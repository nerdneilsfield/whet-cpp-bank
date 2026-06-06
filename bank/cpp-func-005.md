---
qid: cpp-func-005
type: single
kp: [cpp-functions]
difficulty: easy
answer_key: B
---

以下代码执行后，`a` 的值是多少？

```cpp
void doubleIt(int& x) { x *= 2; }
int main() {
    int a = 5;
    doubleIt(a);
    std::cout << a;
}
```

A. `5`
B. `10`
C. `25`
D. 编译错误
