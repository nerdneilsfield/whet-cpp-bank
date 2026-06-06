---
qid: cpp-iv-smart-004
type: short
kp: [cpp-interview]
difficulty: medium
tags: [阿里, Amazon]
rubric:
  - new+shared_ptr 两次堆分配（对象一次，控制块一次），make_shared 合并为一次
  - 合并分配提升 cache locality，减少内存碎片
  - make_shared 的缺点：弱引用存活期间对象内存无法单独释放
  - new 方式支持自定义删除器，make_shared 不支持
  - 异常安全：new 方式在某些调用顺序下有泄漏风险（C++17 已修复求值顺序）
---

# Q: `make_shared` 和 `new` + `shared_ptr` 构造的区别？

## Explanation

### 内存分配次数

```cpp
// 方式一：new + shared_ptr 构造——两次堆分配
std::shared_ptr<Widget> p1(new Widget(args));
//  分配1: new Widget(...)   → 对象本身
//  分配2: 控制块（use_count, weak_count, deleter, allocator）

// 方式二：make_shared——一次堆分配
auto p2 = std::make_shared<Widget>(args);
//  单次分配: [ControlBlock | Widget 对象] 连续内存
```

### 性能对比

| 维度 | `new` + 构造 | `make_shared` |
|------|-------------|---------------|
| 堆分配次数 | 2 | 1 |
| Cache locality | 控制块和对象分离 | 连续，L1 cache 友好 |
| 内存碎片 | 两块碎片 | 一块 |

### `make_shared` 的缺点

由于对象和控制块在同一块内存中，**强引用计数归零不会立即释放对象占用的内存**——必须等 `weak_count` 也归零，控制块才能整体释放。如果对象很大且存在长生命周期的 `weak_ptr`，内存会"虚挂"。

```cpp
// 问题演示（对象 10MB，weak_ptr 长期存活）
auto big = std::make_shared<BigObject>(/* 10MB */);
std::weak_ptr<BigObject> observer = big;

big.reset();   // use_count → 0，对象析构，但 10MB 内存还在
               // 直到 observer 销毁（weak_count → 0），内存才释放

// 用 new 构造则不同：use_count → 0 时对象内存立即 delete
std::shared_ptr<BigObject> big2(new BigObject(/* 10MB */));
std::weak_ptr<BigObject> obs2 = big2;
big2.reset();  // 对象内存立即释放，控制块（几十字节）仍存活
```

### 自定义删除器

```cpp
// make_shared 不支持自定义删除器
auto p = std::make_shared<FILE>(fopen("f.txt","r"));  // 错误：不能传 deleter

// new 方式支持
auto deleter = [](FILE* f){ fclose(f); };
std::shared_ptr<FILE> fp(fopen("f.txt","r"), deleter);
```

### 异常安全（历史问题，C++17 修复）

```cpp
// C++14 之前，下列代码在某些编译器存在泄漏风险：
foo(std::shared_ptr<T>(new T), bar());
// 编译器可能按顺序：① new T，② bar()（抛异常），③ shared_ptr 构造
// ② 抛异常时 ①  已分配的内存无 shared_ptr 持有 → 泄漏

// make_shared 无此问题：new 和控制块构造是一个不可分割的原子步骤
foo(std::make_shared<T>(), bar());  // 安全
// C++17 修复了参数求值顺序，new 方式也安全了
```

**结论：** 默认用 `make_shared`；仅在需要自定义删除器，或对象极大且有长寿 `weak_ptr` 时，才用 `new` 方式构造。
