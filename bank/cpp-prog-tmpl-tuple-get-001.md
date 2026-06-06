---
qid: cpp-prog-tmpl-tuple-get-001
type: prog
kp: [cpp-templates]
primary_kp: cpp-templates
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-tmpl-tuple-get-001/
---
实现自制的 Tuple<Types...> 和 std::get<I>() 函数获取第 I 个元素。使用递归继承。

### 函数签名
```cpp
#pragma once
#include <utility>
#include <type_traits>

template <typename... Types>
class Tuple;

template <std::size_t I, typename T>
struct TupleLeaf {
    T value;
    TupleLeaf() = default;
    TupleLeaf(const T& v) : value(v) {}
    TupleLeaf(T&& v) : value(std::move(v)) {}
};

template <std::size_t I, typename... Types>
struct TupleImpl;

template <std::size_t I, typename T, typename... Rest>
struct TupleImpl<I, T, Rest...> : TupleLeaf<I, T>, TupleImpl<I+1, Rest...> {
    TupleImpl() = default;
    TupleImpl(const T& v, const Rest&... rest)
        : TupleLeaf<I, T>(v), TupleImpl<I+1, Rest...>(rest...) {}
};

template <std::size_t I>
struct TupleImpl<I> {};

template <typename... Types>
class Tuple : public TupleImpl<0, Types...> {
public:
    Tuple() = default;
    Tuple(const Types&... args) : TupleImpl<0, Types...>(args...) {}
};

template <std::size_t I, typename T>
T& get(TupleLeaf<I, T>& leaf) { return leaf.value; }
template <std::size_t I, typename T>
const T& get(const TupleLeaf<I, T>& leaf) { return leaf.value; }
template <std::size_t I, typename T>
T&& get(TupleLeaf<I, T>&& leaf) { return std::move(leaf.value); }
```

### 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## Explanation

递归继承中每个 `TupleLeaf<I,T>` 保存一个位置的值，`TupleImpl` 逐层继承这些 leaf。`get<I>` 利用基类转换找到对应编号的 `TupleLeaf<I,T>`，再返回其中的 `value`。注意要提供 const、非 const 和右值重载，保持引用和值类别正确。
