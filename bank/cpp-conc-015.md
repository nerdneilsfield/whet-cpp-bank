---
qid: cpp-conc-015
type: multi
kp: [cpp-concurrency]
difficulty: easy
answer_key: [A, C, D]
---

# 代码阅读：条件变量用法

```cpp
std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void producer() {
    std::unique_lock<std::mutex> ul(mtx);
    ready = true;
    cv.notify_one();
}

void consumer() {
    std::unique_lock<std::mutex> ul(mtx);
    cv.wait(ul, []{ return ready; });
    // 处理数据
}
```

关于此代码，以下说法**正确**的有（多选）：

A. `cv.wait()` 在谓词为 `false` 时会自动释放 `ul` 并挂起线程  
B. `cv.wait()` 可以与 `std::lock_guard` 配合使用  
C. `notify_one()` 唤醒至多一个在此条件变量上等待的线程  
D. 谓词 `[]{ return ready; }` 可防止虚假唤醒（spurious wakeup）  
E. `producer` 无需加锁也能安全修改 `ready`  
