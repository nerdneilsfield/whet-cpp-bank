---
qid: cpp-bp-concur-001
type: single
kp: [cpp-concurrency]
difficulty: medium
answer_key: D
---

手写 double-checked locking（DCLP）来延迟初始化一个对象：

```cpp
class Widget { /* 重量级对象 */ };

std::atomic<Widget*> global = nullptr;
std::mutex mtx;

Widget* get_widget() {
    if (!global.load(std::memory_order_acquire)) {
        std::lock_guard lk(mtx);
        if (!global.load(std::memory_order_relaxed)) {
            global.store(new Widget(), std::memory_order_release);
        }
    }
    return global;
}
```

哪个选项正确描述了这个实现的可靠性？

A. 完全正确，DCLP 被完美实现
B. 缺少 volatile，不正确
C. 缺少 `atomic_thread_fence`，不正确
D. 虽然正确但没必要——C++11 的 local static 已有线程安全初始化，直接用更简单

---

## Explanation

这个 DCLP 实现**本身是正确的**（使用 `acquire` + `release` 语义确保了 happens-before 关系和 visibility），且在 C++11 之前是唯一可靠的懒初始化方式。

但 C++11 起，**Meyer's initializer**（函数局部 static 变量初始化）已经是**线程安全**的——标准保证：多个线程同时调用同一函数局部 static 变量时，仅一个线程执行初始化，其他线程等待完成。

```cpp
Widget* get_widget() {
    static Widget instance;   // C++11 起线程安全
    return &instance;
}
```

**比 DCLP 好的原因：**
- 代码少 90%，无可读性损失
- 保证线程安全，正确性不可争议
- C++ 编译器本质用的就是 DCLP 类似机制（但 bug-free，用了标准提供的 pthread_once / 自旋 + acquire/release 保证）
- 零额外开销（初始化完成后只是读一次指针）

什么时候 DCLP 还有必要？
1. 初始化非常慢且需要精确控制（如需要传入参数）
2. 需要多个独立的状态变量
3. Local static 有 shutdown order 问题（static 在 `atexit` 清理，顺序和声明顺序相反）

但对于 95% 的延迟初始化场景，Meyer's singleton 就够了。

正确做法：
```cpp
// 一行解决——C++11 起
constexpr auto& get_config() {
    static Config cfg = load_config_from_file();
    return cfg;
}
```
