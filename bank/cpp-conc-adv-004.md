---
qid: cpp-conc-adv-004
type: single
kp: [cpp-concurrency]
difficulty: easy
answer_key: B
---

以下关于函数内 `thread_local static` 变量的描述，哪项正确？

```cpp
void foo() {
    thread_local static int count = 0;
    count++;
    std::cout << count << std::endl;
}
```

A. 所有线程共享同一个 `count`，每次调用都会累加
B. 每个线程有自己独立的 `count`，在同一线程内多次调用 `foo()` 时 `count` 会累加
C. 每次调用 `foo()` 时 `count` 都重置为 0
D. 该写法编译错误，`thread_local` 不能与 `static` 同时使用

## Explanation

正确答案是 B。`thread_local` 对每个线程提供独立对象实例，不能把它当作普通共享全局变量。选项 B 的表述“每个线程有自己独立的 ｀count｀，在同一线程内多次调用 ｀foo()｀ 时 ｀count｀ 会累加”正好符合该规则。A、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
