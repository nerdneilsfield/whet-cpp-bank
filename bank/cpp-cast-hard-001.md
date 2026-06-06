---
qid: cpp-cast-hard-001
type: single
kp: [cpp-casting]
difficulty: hard
answer_key: C
---

`dynamic_cast` 的运行时代价主要来源是？

```cpp
struct A { virtual ~A() = default; };
struct B : A {};

A* a = make();
B* b = dynamic_cast<B*>(a);  // ①
```

A. `dynamic_cast` 是编译期操作，无运行时代价
B. 代价仅为单条指针比较
C. 主要代价来自 RTTI 查找：编译器为每个多态类生成 `type_info` 与继承关系图；`dynamic_cast` 在运行时遍历对象的 vtable，定位 `type_info`，再在继承关系网中搜索目标类型的合法路径（含多重/虚继承），找到则返回调整后的指针，找不到则返回 `nullptr`（指针）或抛 `bad_cast`（引用）。复杂层次下可能是 O(N) 甚至更高
D. `dynamic_cast` 直接等价于 `static_cast`，二者性能相同

## 解析

`dynamic_cast` 在运行时执行"类型安全的向下/横向转换"，必须验证对象的**实际动态类型**与目标类型的关系。典型实现（Itanium ABI）通过对象的 vptr 找到 `type_info` 结构，再遍历基类链/继承图查找目标类型——单一线性继承下接近 O(1) 常数代价；多重继承下需路径搜索；虚继承场景更复杂。微基准测试常显示 `dynamic_cast` 比 `static_cast` 慢 10–50 倍。`final` 关键字可帮助优化（编译器在 `dynamic_cast<Final*>` 时可能内联检查）。性能敏感的热路径中，常用其他模式替代（如双重分派、visitor 模式、tagged enum）。