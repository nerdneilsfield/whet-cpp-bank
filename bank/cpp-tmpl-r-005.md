---
qid: cpp-tmpl-r-005
type: single
kp: [cpp-templates]
difficulty: easy
answer_key: B
---

### 题目

下面代码能否通过编译？若不能，指出原因。

```cpp
#include <iostream>
#include <vector>

void print_first(std::vector<int>& v) {
    std::cout << v[0] << std::endl;
}

int main() {
    std::vector<int> vi = {1, 2, 3};
    std::vector<double> vd = {1.1, 2.2, 3.3};
    print_first(vi);
    print_first(vd);
    return 0;
}
```

A. 两行都正常输出
B. 编译错误：`std::vector<double>` 不能传给接受 `std::vector<int>&` 的函数
C. 运行时崩溃
D. 输出 `1` 和 `1`

## Explanation

B


`std::vector<int>` 和 `std::vector<double>` 是同一类模板的两个不同实例化，它们是完全独立的类型，没有继承关系。`print_first` 接受 `std::vector<int>&`，传入 `std::vector<double>` 类型不匹配，编译报错。如需兼容多种 vector，应将 `print_first` 改为函数模板：`template<typename T> void print_first(std::vector<T>& v)`。
