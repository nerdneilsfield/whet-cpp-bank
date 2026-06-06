---
qid: cpp-tmpl-r-002
type: single
kp: [cpp-templates]
difficulty: easy
answer_key: B
---

## 题目

下面代码输出是什么？

```cpp
#include <iostream>

template<int N>
void print_size() {
    std::cout << N << std::endl;
}

int main() {
    print_size<4>();
    print_size<8>();
    return 0;
}
```

A. 编译错误：非类型模板参数不合法
B. 输出两行：`4` 和 `8`
C. 输出一行：`4`
D. 输出两行：`0` 和 `0`

## 答案

B

## 解析

`template<int N>` 是非类型模板参数，`N` 在编译期确定。`print_size<4>()` 和 `print_size<8>()` 是两个不同的模板实例化，编译器为每个具体值单独生成函数体，分别输出 `4` 和 `8`。非类型模板参数常用于固定大小数组、编译期常量等场景。
