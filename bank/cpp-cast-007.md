---
qid: cpp-cast-007
type: single
kp: [cpp-casting]
difficulty: easy
answer_key: A
---

# explicit 阻止隐式转换

```cpp
struct Meter {
    explicit Meter(double v) : val(v) {}
    double val;
};

void print(Meter m) {}

int main() {
    print(3.14);   // 行 A
    print(Meter(3.14)); // 行 B
}
```

哪一行会导致编译错误？

A. 行 A
B. 行 B
C. 两行都不会
D. 两行都会
