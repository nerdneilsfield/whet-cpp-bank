---
qid: cpp-mem-med-010
type: single
kp: [cpp-memory-mgmt]
difficulty: medium
answer_key: C
---

希望一个容器存放多种不同删除策略的 `unique_ptr<FILE>`（有的关文件，有的发送给关闭服务，有的什么也不做），下列写法中合理的是？

A. `std::vector<std::unique_ptr<FILE>>`，默认删除器即可统一管理所有策略
B. `std::vector<std::unique_ptr<FILE, decltype([](FILE*){})>>`，把所有删除器统一成 lambda
C. `std::vector<std::unique_ptr<FILE, std::function<void(FILE*)>>>`，用 `std::function` 做类型擦除统一删除器类型
D. 无法实现，`unique_ptr` 模板里的删除器类型不可擦除

---

**解析：**

`std::unique_ptr<T, D>` 的删除器类型 `D` 是模板参数的一部分，所以**不同删除器类型的 `unique_ptr` 是不同类型**，不能放进同一个 `std::vector`（A、B 不能容纳多种策略）。

要在容器里混合不同删除策略，需要一个能装下所有可调用对象的"统一删除器类型"。`std::function<void(FILE*)>` 正是这种类型擦除容器：它能存任何签名匹配的函数、lambda、函数对象，运行时通过虚函数派发实际调用。于是：

```cpp
using FilePtr = std::unique_ptr<FILE, std::function<void(FILE*)>>;
std::vector<FilePtr> v;
v.emplace_back(std::fopen("a", "r"), [](FILE* f){ std::fclose(f); });
v.emplace_back(stdout, [](FILE*){});            // 不关闭
v.emplace_back(open_remote(),  &send_to_close_service);
```

代价：`std::function` 内部可能有小对象优化，但通常每个 `unique_ptr` 会变大（额外几十字节），调用删除器有一次间接调用，编译器无法内联。这就是 `unique_ptr` "零开销"承诺的对立面——只有在你确实需要异质删除器时才用这种方案，否则应当让 `D` 在编译期固定以获得 `sizeof(unique_ptr)==sizeof(T*)` 的最佳布局。D 错，正是这种类型擦除的存在反驳了它。

## Explanation

正确答案是 C，`unique_ptr` 的删除器类型属于对象类型的一部分，不同 lambda 或不同函数对象会产生不同的 `unique_ptr` 类型。若要把多种删除策略放进同一个 `vector`，需要统一删除器类型，`std::function<void(FILE*)>` 可做类型擦除。代价是可能有额外存储和间接调用开销，但能满足异构删除策略的容器需求。
