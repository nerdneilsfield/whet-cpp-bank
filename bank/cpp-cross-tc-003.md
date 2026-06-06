---
qid: cpp-cross-tc-003
type: single
kp: [cpp-templates, cpp-containers]
difficulty: easy
answer_key: A
---

以下代码输出是什么？

```cpp
#include <iostream>
#include <array>

template<int N>
std::array<int, N> makeIota() {
    std::array<int, N> a;
    for (int i = 0; i < N; ++i) a[i] = i + 1;
    return a;
}

int main() {
    auto a3 = makeIota<3>();
    auto a5 = makeIota<5>();
    std::cout << a3[2] << "\n";
    std::cout << a5[4] << "\n";
    return 0;
}
```

A. `3\n5\n`  
B. `2\n4\n`  
C. `1\n1\n`  
D. 编译错误，`N` 不能用于 `std::array` 的大小参数

<!--
非类型模板参数 N 是编译期常量，合法用作 std::array 的大小。
makeIota<3>：a = {1,2,3}，a3[2] = 3。
makeIota<5>：a = {1,2,3,4,5}，a5[4] = 5。
-->

## 解析

A 正确：非类型模板参数 `N` 是编译期常量，可以作为 `std::array<int, N>` 的长度。`makeIota<3>` 填入 1、2、3，`makeIota<5>` 填入 1 到 5，因此访问下标 2 和 4 分别得到 3 和 5。关键误区是认为模板参数只能表示类型，不能表示整数常量。
