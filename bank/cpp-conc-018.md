---
qid: cpp-conc-018
type: multi
kp: [cpp-concurrency]
difficulty: easy
answer_key: [B, D]
---

# 代码阅读：`join` vs `detach` 选择

```cpp
void background_log() {
    // 写日志，耗时不定
}

int main() {
    std::thread logger(background_log);
    // 选项 X: logger.join();
    // 选项 Y: logger.detach();
    return 0;
}
```

以下说法**正确**的有（多选）：

A. 选项 X 和 Y 均会导致 `std::terminate()`  
B. 选项 X：`main` 会阻塞等待 `background_log` 完成后再退出  
C. 选项 Y：程序退出时保证 `background_log` 已执行完毕  
D. 选项 Y：线程与 `logger` 对象解关联，`main` 不等待它完成  
E. 两个选项都不合法，必须两个都调用  
