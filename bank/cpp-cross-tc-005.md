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

## 解析

B 正确：`sumFirst` 只有一个模板参数 `T`，两个形参都要求是 `std::vector<T>`。传入 `vector<int>` 推导出 `T=int`，传入 `vector<double>` 又推导出 `T=double`，发生推导冲突。关键误区是认为模板实参推导会自动把 `vector<int>` 转成 `vector<double>`；容器类型之间不会这样隐式转换。
