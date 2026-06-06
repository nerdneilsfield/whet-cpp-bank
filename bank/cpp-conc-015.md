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

## Explanation

正确答案是 A、C、D。互斥量通过临界区保护共享状态，适合多步复合操作而不只是单个原子读写。 A 正确：｀cv.wait()｀ 在谓词为 ｀false｀ 时会自动释放 ｀ul｀ 并挂起线程；B 错误：｀cv.wait()｀ 可以与 ｀std::lock_guard｀ 配合使用；C 正确：｀notify_one()｀ 唤醒至多一个在此条件变量上等待的线程；D 正确：谓词 ｀[]{ return ready; }｀ 可防止虚假唤醒（spurious wakeup）；E 错误：｀producer｀ 无需加锁也能安全修改 ｀ready｀。常见误区是只记住术语名称，而忽略每个选项中的限定条件、生命周期、同步关系或复杂度前提。
