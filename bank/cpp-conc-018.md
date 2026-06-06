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

## Explanation

正确答案是 B、D。并发题的核心是同步关系、数据竞争和原子/锁的适用边界。 A 错误：选项 X 和 Y 均会导致 ｀std::terminate()｀；B 正确：选项 X：｀main｀ 会阻塞等待 ｀background_log｀ 完成后再退出；C 错误：选项 Y：程序退出时保证 ｀background_log｀ 已执行完毕；D 正确：选项 Y：线程与 ｀logger｀ 对象解关联，｀main｀ 不等待它完成；E 错误：两个选项都不合法，必须两个都调用。常见误区是只记住术语名称，而忽略每个选项中的限定条件、生命周期、同步关系或复杂度前提。
