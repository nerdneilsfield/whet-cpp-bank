---
qid: cpp-conc-hard-012
type: single
kp: [cpp-concurrency]
difficulty: hard
answer_key: A
---

以下是没有正确内存序的 double-checked locking 经典实现：

```cpp
class Singleton {
    static Singleton* instance;   // 普通指针，非原子
    static std::mutex mtx;
public:
    static Singleton* getInstance() {
        if (instance == nullptr) {          // (1) 第一次检查，无同步
            std::lock_guard<std::mutex> lock(mtx);
            if (instance == nullptr) {      // (2) 第二次检查
                instance = new Singleton(); // (3) 分配 + 构造 + 赋值
            }
        }
        return instance;
    }
};
```

为什么 `(1)` 处读到 `instance != nullptr` 后，使用该指针仍可能访问未完全初始化的对象？

A. `(3)` 在底层分为三步：分配内存、调用构造函数、将地址写入 `instance`。编译器/CPU 可将这三步重排为：分配内存、将地址写入 `instance`、调用构造函数。另一线程在 `(1)` 读到非空指针，但对象尚未构造完成
B. `std::mutex` 的 `lock` 不提供 `acquire` 语义，无法阻止 `(3)` 的写操作被看到
C. `new` 操作符不是原子的，两个线程可能同时进入 `(3)` 导致双重构造
D. `(1)` 处读取 `instance` 是 UB，因为没有锁保护，但只要读到非空就说明初始化已完成

## 解析

正确答案是 A。`nullptr` 的类型是 `std::nullptr_t`，它不会像 `NULL` 那样被当作整数参与重载解析。选项 A 的表述“｀(3)｀ 在底层分为三步：分配内存、调用构造函数、将地址写入 ｀instance｀。编译器/CPU 可将这三步重排为：分配内存、将地址写入 ｀instance｀、调用构造函数。另一线程在 ｀(1)｀ 读到非空指针，但对象尚未构造完成”正好符合该规则。B、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
