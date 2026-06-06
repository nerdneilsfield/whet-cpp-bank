---
qid: cpp-prog-tmpl-tuple-001
type: prog
kp: [cpp-templates]
primary_kp: cpp-templates
difficulty: hard
toolchain: [make]
tests_dir: tests/cpp-prog-tmpl-tuple-001/
---
实现极简 MyTuple<Ts...>，支持 get<I>(t) 取得第 I 个元素引用。递归继承法。

### 函数签名
```cpp
// solution.hpp
#pragma once
#include <cstddef>

template <class... Ts>
struct MyTuple;

template <>
struct MyTuple<> {};

template <class Head, class... Tail>
struct MyTuple<Head, Tail...> {
    Head head;
    MyTuple<Tail...> tail;
    MyTuple() = default;
    MyTuple(Head h, Tail... t);
};

template <std::size_t I, class... Ts>
struct TupleGetter;

template <std::size_t I, class T>
auto& get(T& t);
```

### 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## Explanation
递归继承/递归成员的核心是把第一个元素存在 `head`，其余元素存在 `tail`。`get<0>` 返回当前层的 `head`，`get<I>` 递归到 `tail` 上取 `I-1`。构造函数也要递归初始化，注意返回引用而不是值，否则测试会无法修改原 tuple 元素。
