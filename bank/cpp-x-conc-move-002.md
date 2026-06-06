---
qid: cpp-x-conc-move-002
type: single
kp: [cpp-concurrency, cpp-move-semantics]
primary_kp: cpp-concurrency
difficulty: medium
answer_key: B
---

下列代码使用 `std::promise` 和 `std::future`，哪一行会编译失败？

```cpp
#include <future>
#include <thread>
#include <utility>

int main() {
    std::promise<int> p1;
    std::future<int>  f1 = p1.get_future();

    std::promise<int> p2 = p1;                  // (A)
    std::promise<int> p3 = std::move(p1);       // (B)

    std::future<int>  f2 = f1;                  // (C)
    std::future<int>  f3 = std::move(f1);       // (D)

    return 0;
}
```

A. 只有 (A) 失败
B. (A) 和 (C) 失败
C. (B) 和 (D) 失败
D. 全部成功

---

## Explanation

`std::promise<T>` 和 `std::future<T>` 都被设计为 **不可拷贝但可移动** 的资源句柄：

```cpp
// 摘要：
template <class T> class promise {
    promise(const promise&) = delete;           // 禁止拷贝
    promise(promise&&) noexcept;                // 允许移动
    promise& operator=(const promise&) = delete;
    promise& operator=(promise&&) noexcept;
};

template <class T> class future {
    future(const future&) = delete;             // 禁止拷贝
    future(future&&) noexcept;                  // 允许移动
};
```

原因：
- `promise` 持有一个 **共享状态（shared state）**，只能由一个写入端持有。允许拷贝会导致多个 promise 写入同一个状态，违反 happens-before 语义。
- `future` 同样持有共享状态的读取端。一次 `get()` 只能由一个调用方完成（C++14 起的 `shared_future` 才能拷贝、多次 get）。

逐项分析：

- **(A) `std::promise<int> p2 = p1;`** — 拷贝构造，**编译失败**：拷贝构造函数 deleted。
- **(B) `std::promise<int> p3 = std::move(p1);`** — 移动构造，**合法**，`p1` 被掏空，`p3` 接管共享状态。
- **(C) `std::future<int> f2 = f1;`** — 拷贝构造，**编译失败**：拷贝构造函数 deleted。
- **(D) `std::future<int> f3 = std::move(f1);`** — 移动构造，**合法**，`f1` 被掏空。

如果需要多个消费者：

```cpp
std::shared_future<int> sf = f1.share();   // 转为 shared，可拷贝
auto sf2 = sf;                             // 合法
```

`std::shared_future::get()` 可以多次调用，每次都返回共享状态中的值（或对左值返回 const 引用）。但 `std::promise` 没有共享版本——写入端必须严格唯一。

相关的「专门可移动不可拷贝」类型还包括：`std::unique_ptr`、`std::thread`、`std::jthread`、`std::packaged_task`、`std::unique_lock`、`std::ifstream`/`std::ofstream` 等。设计模式上，凡持有 **独占资源** 的 RAII 类，都遵循这个规则。
