---
qid: cpp-prog-smf-rule-of-zero-001
type: prog
kp: [cpp-special-members]
primary_kp: cpp-special-members
difficulty: easy
toolchain: [make]
tests_dir: tests/cpp-prog-smf-rule-of-zero-001/
---
RuleOfZero 类使用 std::vector<int> 和 std::string 成员。依赖编译器生成的默认构造、析构、拷贝/移动构造、拷贝/移动赋值运算符。验证全部 6 个 SMF 正确工作。

### 函数签名
```cpp
#pragma once
#include <vector>
#include <string>

class RuleOfZero {
public:
    RuleOfZero() = default;
    // 编译器生成: 析构, 拷贝/移动构造, 拷贝/移动赋值
    std::vector<int> vec;
    std::string str;
};
```

### 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## Explanation

Rule of Zero 的核心是让 `std::vector` 和 `std::string` 自己管理资源，类本身不声明析构、拷贝或移动特殊成员。编译器生成的默认操作会逐成员正确拷贝或移动。误区是为了“完整”手写六个特殊成员，反而可能破坏默认的异常安全和移动语义。
