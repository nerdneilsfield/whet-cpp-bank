---
qid: cpp-tmp-hard-008
type: single
kp: [cpp-templates]
difficulty: hard
answer_key: C
---

以下代码使用 fold 表达式检查所有参数是否均为真：

```cpp
template<typename... Args>
bool all_true(Args... args) {
    return (args && ...);
}
```

调用 `all_true(true, 1, 0, true)` 的返回值是？

A. `true`
B. 编译错误，`&&` 不能用于 fold 表达式
C. `false`
D. 未定义行为
