---
qid: cpp-cross-tc-005
type: single
kp: [cpp-templates, cpp-containers]
difficulty: easy
answer_key: B
---

以下代码的编译结果是什么？

```cpp
#include <vector>
#include <iostream>

template<typename T>
T sumFirst(const std::vector<T>& a, const std::vector<T>& b) {
    return a[0] + b[0];
}

int main() {
    std::vector<int>    vi = {1, 2};
    std::vector<double> vd = {1.5, 2.5};
    auto r = sumFirst(vi, vd);   // (*)
    std::cout << r << "\n";
    return 0;
}
```

A. 正常编译，输出 `2.5`（`int` 隐式转换为 `double`）  
B. 编译错误：模板参数 `T` 推导冲突（`int` vs `double`）  
C. 正常编译，输出 `2`（`double` 截断为 `int`）  
D. 编译错误：`operator+` 不支持 `int` 与 `double`

<!--
函数模板 sumFirst 要求两个参数的 T 相同。
调用 (*) 处，第一个参数推导 T=int，第二个推导 T=double，产生冲突。
编译器报错：deduced conflicting types for parameter 'T'。
修复方式：显式指定 sumFirst<double>(vi, vd) 或使用两个独立类型参数。
-->
