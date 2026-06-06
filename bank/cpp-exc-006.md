---
qid: cpp-exc-006
type: single
kp: [cpp-exceptions]
difficulty: easy
answer_key: D
---

# C++ 异常处理：异常类型匹配规则

有如下 catch 块序列（从上到下）：

```cpp
catch (std::exception& e) { /* A */ }
catch (std::runtime_error& e) { /* B */ }
```

抛出 `std::runtime_error` 时，哪个 catch 块会被执行？

A. B，因为更具体
B. 两个都执行
C. 编译错误，无法确定
D. A，因为 `runtime_error` 是 `exception` 的子类，先匹配基类
