---
qid: cpp-prog-smf-bigfive-001
type: prog
kp: [cpp-special-members]
primary_kp: cpp-special-members
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-smf-bigfive-001/
---
实现 IntArray：管理动态 int[]。构造接受 size 与初值，提供五大特殊成员。size()、at(i) 返回值。

### 函数签名
```cpp
// solution.hpp
#pragma once
#include <cstddef>
#include <utility>
#include <algorithm>

class IntArray {
public:
    IntArray(std::size_t n, int v);
    ~IntArray();
    IntArray(const IntArray& o);
    IntArray(IntArray&& o) noexcept;
    IntArray& operator=(const IntArray& o);
    IntArray& operator=(IntArray&& o) noexcept;
    std::size_t size() const noexcept;
    int at(std::size_t i) const;
private:
    int* data_;
    std::size_t n_;
};
```

### 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## Explanation
这是典型管理裸数组资源的五大特殊成员题。构造分配 `n` 个 `int` 并填充值，析构释放；拷贝构造/赋值要深拷贝，移动构造/赋值要转移指针并把源对象置为空状态。赋值要处理自赋值和旧资源释放，`at(i)` 应按测试要求处理越界，通常抛 `std::out_of_range`。
