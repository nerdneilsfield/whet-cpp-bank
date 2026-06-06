---
qid: cpp-prog-move-string-001
type: prog
kp: [cpp-move-semantics]
primary_kp: cpp-move-semantics
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-move-string-001/
---
实现简化 String（无 SSO）：构造自 const char*、析构、深拷贝、移动构造/赋值、size、c_str。

### 函数签名
```cpp
// solution.hpp
#pragma once
#include <cstddef>
#include <cstring>
#include <utility>

class String {
public:
    String();
    String(const char* s);
    ~String();
    String(const String& o);
    String(String&& o) noexcept;
    String& operator=(const String& o);
    String& operator=(String&& o) noexcept;
    std::size_t size() const noexcept;
    const char* c_str() const noexcept;
private:
    char* data_;
    std::size_t size_;
};
```

### 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## Explanation
字符串对象需要维护以 `\0` 结尾的动态字符数组和长度。构造自 `const char*` 时处理空指针或空串边界，拷贝构造/赋值做深拷贝，移动构造/赋值转移指针并让源对象变成有效空串状态。赋值时注意自赋值和旧内存释放，`c_str()` 应始终返回可用的 C 字符串。
