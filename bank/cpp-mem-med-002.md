---
qid: cpp-mem-med-002
type: single
kp: [cpp-memory-mgmt]
difficulty: medium
answer_key: B
---

关于 `std::unique_ptr<T, D>` 的自定义删除器 `D`，下列说法正确的是？

```cpp
auto del = [](FILE* f) { std::fclose(f); };
std::unique_ptr<FILE, decltype(del)> fp(std::fopen("a.txt", "r"), del);
```

A. 自定义删除器不影响 `unique_ptr` 的大小，永远是单指针
B. 删除器类型是 `unique_ptr` 模板参数的一部分，不同删除器类型的 `unique_ptr` 互不兼容
C. `unique_ptr` 的自定义删除器会在运行时做类型擦除，类似 `std::function`
D. 自定义删除器必须是函数指针，不能用 lambda

---

**解析：**

`std::unique_ptr` 的删除器类型是模板第二参数，编译期就确定，**没有任何类型擦除开销**。当删除器是空的 lambda 或函数对象时，通过 EBO（空基类优化）可以做到 `sizeof(unique_ptr) == sizeof(T*)`；若删除器是函数指针或有状态的对象，`unique_ptr` 会变大（A 错）。

由于删除器写进了类型，`unique_ptr<FILE, decltype(del1)>` 与 `unique_ptr<FILE, decltype(del2)>` 是两种不同类型，不能互相赋值或放进同一个容器（B 正确）。这与 `std::shared_ptr` 不同——后者用类型擦除把删除器藏进控制块，所以删除器不进入 `shared_ptr` 的模板参数（C 错，C 描述的是 `shared_ptr` 的行为）。删除器可以是任何可调用对象（D 错）。