---
qid: cpp-cross-tc-001
type: single
kp: [cpp-templates, cpp-containers]
difficulty: easy
answer_key: B
---

以下代码输出是什么？

```cpp
#include <iostream>
#include <vector>
#include <string>

template<typename T>
void printAll(const std::vector<T>& v) {
    for (const auto& x : v) {
        std::cout << x << " ";
    }
    std::cout << "\n";
}

int main() {
    std::vector<int> vi = {1, 2, 3};
    std::vector<std::string> vs = {"a", "b"};
    printAll(vi);
    printAll(vs);
    return 0;
}
```

A. 编译错误，模板不能接受 `std::string`  
B. `1 2 3 \na b \n`（各占一行，末尾有空格）  
C. `1 2 3 a b`（全在一行）  
D. `a b \n1 2 3 \n`（顺序相反）

<!--
编译器为 printAll<int> 和 printAll<std::string> 各生成一份实例。
第一次调用输出 "1 2 3 \n"，第二次输出 "a b \n"。
T 只要支持 operator<< 即可实例化，std::string 满足条件。
-->

## Explanation

B 正确：函数模板会分别为 `std::vector<int>` 和 `std::vector<std::string>` 实例化。两个类型都支持输出到 `std::cout`，因此依次打印整数行和字符串行。关键误区是认为模板只能处理数值类型；模板约束来自函数体中实际使用的操作。
