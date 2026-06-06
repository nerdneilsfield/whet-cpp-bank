---
qid: cpp-prog-tmpl-variant-001
type: prog
kp: [cpp-templates]
primary_kp: cpp-templates
difficulty: hard
toolchain: [make]
tests_dir: tests/cpp-prog-tmpl-variant-001/
---
实现简化的 Variant<T1,T2>，支持存储两种类型之一。提供构造、析构、type_tag() 和 visit(Func) 方法。

### 函数签名
```cpp
#pragma once
#include <cstddef>
#include <new>
#include <type_traits>

template <typename T1, typename T2>
class Variant {
public:
    Variant();
    Variant(const T1& v);
    Variant(const T2& v);
    Variant(T1&& v);
    Variant(T2&& v);
    ~Variant();
    Variant(const Variant& o);
    Variant(Variant&& o) noexcept;
    int type_tag() const noexcept;
    template <typename Visitor>
    decltype(auto) visit(Visitor&& vis);
    template <typename Visitor>
    decltype(auto) visit(Visitor&& vis) const;
};
```

### 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## Explanation

Variant 可用 `std::aligned_storage` 或联合式缓冲区保存 T1/T2 中的一个，并用 tag 记录当前活动类型。构造时 placement new 对应类型，析构、拷贝和移动都根据 tag 分派到正确类型操作。`visit` 也按 tag 调用 visitor；关键是任何时候只能析构当前真正构造过的对象。
