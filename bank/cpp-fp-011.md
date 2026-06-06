---
qid: cpp-fp-011
type: single
kp: [cpp-function-pointers]
difficulty: easy
answer_key: A
---

# 代码阅读：函数指针作为回调参数

```cpp
#include <iostream>

void apply(int* arr, int n, int (*transform)(int)) {
    for (int i = 0; i < n; ++i)
        arr[i] = transform(arr[i]);
}

int doubled(int x) { return x * 2; }

int main() {
    int a[] = {1, 2, 3};
    apply(a, 3, doubled);
    std::cout << a[1];
}
```

输出是？

A. 4  
B. 2  
C. 6  
D. 编译错误

## Explanation

正确答案是 A，对应“4”。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。其他选项容易混淆相关概念：B 项“2”不满足题干要求；C 项“6”不满足题干要求；D 项“编译错误”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
