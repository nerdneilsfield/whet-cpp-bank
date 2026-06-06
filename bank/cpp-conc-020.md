---
qid: cpp-conc-020
type: fill
kp: [cpp-concurrency]
difficulty: easy
answer_key: "notify_all"
---

# 代码阅读：唤醒所有等待线程

```cpp
std::condition_variable cv;

// 当共享状态变为就绪后，需要唤醒所有在 cv 上等待的消费者线程
cv.____(  );  // 填写正确的成员函数调用
```

空白处应填写条件变量的成员函数名（不含括号）____。
