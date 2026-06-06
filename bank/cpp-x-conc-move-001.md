---
qid: cpp-x-conc-move-001
type: single
kp: [cpp-concurrency, cpp-move-semantics]
primary_kp: cpp-concurrency
difficulty: medium
answer_key: D
---

下列代码关于 `std::thread` 的参数传递，行为正确的是？

```cpp
#include <thread>
#include <iostream>

struct Worker {
    int id_;
    Worker(int id) : id_(id) {}
    Worker(const Worker&) = delete;
    Worker(Worker&&) = default;
    void operator()() const {
        std::cout << id_ << "\n";
    }
};

int main() {
    Worker w{42};
    std::thread t(w);       // (A) — 这里
    // std::thread t2(std::move(w));  // (B)
    t.join();
}
```

A. (A) 编译失败，因为 `Worker` 不可拷贝
B. (A) 合法，`t` 内部持有 `w` 的引用
C. (A) 合法，`t` 内部持有 `w` 的副本（但 Worker 不可拷贝，实为副本 = 编译失败）
D. (A) 编译失败；(B) 如果替换上去，线程内部使用 `std::move(w)` 转移所有权

---

**解析：**

`std::thread` 的构造函数 `thread(F&& f, Args&&... args)` 把 **所有参数（包括可调用对象 `f`）按值复制存储到线程内部**（线程内的安全拷贝），随后在新线程上调用 `std::invoke`。

逐个分析：

- **(A)** `std::thread t(w)` — 需要复制 `w` 到线程内部。但 `Worker` 的拷贝构造函数已 `= delete`，**编译失败**。编译器错误信息大致为 "attempting to reference a deleted function"。
- **(B)** 如果改为 `std::thread t(std::move(w))` — 匹配到 `std::thread t(Worker&&)`，线程内部通过 **移动构造** 持有 `Worker` 的副本。`w.id_` 被转移到线程内部副本，主线程的 `w` 处于移后状态（id_ 可能变为未指定值）。**合法**。

扩展要点：

**`std::thread` 的参数总是被复制/移动到线程内部**。这与 `std::bind`、`std::function` 等一致，目的是避免数据竞争和悬空引用。线程函数内部的引用不会绑定到主线程的变量，除非显式使用 `std::ref`：

```cpp
int counter = 0;
std::thread t([&counter]{ ++counter; });  // 引用捕获，线程内持有 counter 的引用
// 或
std::thread t(std::bind(/* ... */));
```

**C++20 起 `std::jthread`** 继承自 `std::thread` 但增加了自动 `join` 析构和协作式中断支持：

```cpp
std::jthread jt(std::move(w));  // 自动 join on destruct
```

注意：把 `std::thread` 本身移动给另一个 `std::thread`（`std::thread t2 = std::move(t1)`）转移的是线程句柄，不是线程函数的参数——这是两回事。