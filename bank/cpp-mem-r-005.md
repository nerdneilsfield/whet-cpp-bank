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

正确答案是 B，直接 `shared_ptr<int>(new int(1))` 通常先分配 `int`，再为控制块分配内存。`make_shared<int>(1)` 通常把对象和控制块合并为一次分配，减少开销并改善局部性。两者语义同为共享所有权，也都支持配合 `weak_ptr` 使用。
