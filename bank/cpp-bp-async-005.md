---
qid: cpp-bp-async-005
type: single
kp: [cpp-concurrency]
difficulty: medium
answer_key: C
---

C++ 标准目前缺乏正式的 "executor" 抽象（C++26 计划引入）。如何在 C++17/20 中实现一个"投递任务到指定执行器"的可组合 API？

```cpp
class Executor {
public:
    virtual void post(std::function<void()> task) = 0;
    virtual ~Executor() = default;
};

class ThreadPool : public Executor { ... };
class InlineExecutor : public Executor { void post(std::function<void()> t) override { t(); } };

// 想做：在 executor 上异步执行 f，返回 future
template<class F>
auto spawn(Executor& exec, F f) -> ???
```

A. 直接调用 exec.post(f)，无 future
B. 用 std::async(std::launch::async, f) 完全忽略 executor
C. 用 promise/packaged_task 在 post 内手动 set_value，返回关联 future
D. 用 std::thread + executor，实际上启了新线程

---

**解析：**

C++ 标准没有 executor 抽象（C++26 才正式引入 `std::execution` 框架，灵感来源于 `sender/receiver` 提案）。在没有标准库支持时，工程上典型做法是**自己组合 `packaged_task` + `executor`**：

```cpp
template<class F>
auto spawn(Executor& exec, F f) -> std::future<std::invoke_result_t<F>> {
    using R = std::invoke_result_t<F>;
    auto task = std::make_shared<std::packaged_task<R()>>(std::move(f));
    auto fut = task->get_future();
    exec.post([task] { (*task)(); });    // 在 executor 上执行 task
    return fut;
}

// 使用
ThreadPool pool(8);
auto fut = spawn(pool, []{ return heavy_compute(); });
int r = fut.get();
```

要点：
1. `packaged_task` 用 `shared_ptr` 包装，因 `std::function` 要求被包装的可调用对象**可拷贝**，而 `packaged_task` 是 move-only
2. `post` 接受 `function<void()>`，所以需要把 task 用 lambda 包一层
3. 返回 `future<R>`，调用方按需 `get()`

这种"executor-like + packaged_task"模式被 Boost.Asio、folly、Seastar 等大量项目使用，是 C++26 标准化前的事实标准。

对比其他选项：
- A：丢失了"获取结果"的能力，回调地狱
- B：完全忽略 executor，等于没用——`std::async` 创建自己的线程
- D：每个 spawn 都启一个线程，executor 形同虚设

注意：C++26 `std::execution` 将引入 `sender/receiver` 模型，比简单的 executor 强大得多（支持组合、取消、错误传播）。但在那之前，"executor + packaged_task" 是工程最优解。