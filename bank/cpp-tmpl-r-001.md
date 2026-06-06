---
qid: cpp-tmpl-r-001
type: single
kp: [cpp-templates]
difficulty: easy
answer_key: C
---

### 题目

下面代码能否通过编译？若能，输出是什么？

```cpp
#include <iostream>

template<typename T>
T mymax(T a, T b) {
    return a > b ? a : b;
}

int main() {
    std::cout << mymax(1, 2.0) << std::endl;
    return 0;
}
```

A. 输出 `2`
B. 输出 `2.0`
C. 编译错误：模板参数推导冲突
D. 输出 `1`

## Explanation

C


`mymax(1, 2.0)` 中，`1` 推导出 `T = int`，`2.0` 推导出 `T = double`，两次推导结果不同，编译器无法确定 `T` 应为哪种类型，报错：`deduced conflicting types for parameter 'T'`。修复方式：显式指定 `mymax<double>(1, 2.0)` 或让参数类型一致。
