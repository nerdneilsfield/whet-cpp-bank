---
qid: cpp-tmp-hard-003
type: single
kp: [cpp-templates]
difficulty: hard
answer_key: B
---

以下代码试图递归计算阶乘，但存在问题：

```cpp
template<int N>
struct Factorial {
    static constexpr int value = N * Factorial<N - 1>::value;
};

// 缺少终止特化

int main() {
    int x = Factorial<5>::value;
}
```

编译该代码会发生什么？

A. 正常编译，`x = 120`
B. 编译失败，因为模板递归无终止条件，实例化无限展开
C. 运行时崩溃，栈溢出
D. `x = 0`，因为编译器自动将负数实例化截断
