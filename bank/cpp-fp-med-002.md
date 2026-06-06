---
qid: cpp-fp-med-002
type: single
kp: [cpp-function-pointers]
difficulty: medium
answer_key: B
---

`std::function` 和裸函数指针在性能和语义上的差异，以下哪条表述**正确**？

```cpp
void f(int) {}
auto lambda = [](int) {};
std::function<void(int)> ff = f;
std::function<void(int)> fl = lambda;
```

A. `ff` 和 `fl` 性能相同，因为 `std::function` 对两者都做类型擦除
B. `ff` 可能比 `fl` 更快，因为无捕获 lambda 的 SBO 比函数指针的 SBO 更优
C. `std::function` 总是比裸函数指针慢至少一个间接调用
D. `std::function` 对小可调用对象（包括函数指针）使用 SBO，对捕获过多的 lambda 才动态分配

---

**解析：**

`std::function` 实现通常使用小对象优化（SBO/Small Buffer Optimization）：当可调用对象的大小不超过实现预设的缓冲区（通常 16-32 字节）时，直接存储而非堆分配。

- 函数指针（通常 8 字节）可以 SBO 存储，零堆开销。
- 无捕获 lambda 等价于函数指针，同样可以 SBO。
- 有多个捕获的 lambda 可能超过 SBO 大小，触发动态分配。

所以 `ff`（存储函数指针）和 `fl`（存储无捕获 lambda）都走 SBO 路径，无堆分配。性能比裸函数指针多一次虚函数调用（通过 `operator()` 内部），但这不是"至少一个间接调用"那么糟糕——编译器可以内联某些情况。