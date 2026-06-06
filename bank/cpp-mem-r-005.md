---
qid: cpp-mem-r-005
type: single
kp: [cpp-memory-mgmt]
difficulty: easy
answer_key: "B"
---

## 题目

以下两段代码在分配行为上的主要区别是什么？

```cpp
// 方式 A
auto sp1 = std::shared_ptr<int>(new int(1));

// 方式 B
auto sp2 = std::make_shared<int>(1);
```

A. 方式 B 不合法，`make_shared` 只能用于自定义类，不能用于内置类型
B. 方式 A 进行两次内存分配（对象一次，控制块一次）；方式 B 只进行一次内存分配（对象与控制块合并）
C. 两者完全等价，无任何区别
D. 方式 B 创建的 `shared_ptr` 不支持 `weak_ptr`

## 解析

`shared_ptr<T>(new T(...))` 先分配 `T` 对象，再分配 `shared_ptr` 的控制块（引用计数等），共两次堆分配。`make_shared<T>(...)` 将两者合并为一次分配，减少分配次数和内存碎片，是推荐用法。
