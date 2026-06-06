---
qid: cpp-lambda-med-002
type: single
kp: [cpp-lambdas]
difficulty: medium
answer_key: A
---
下列代码输出是？

```cpp
#include <iostream>
int main() {
    int cnt = 0;
    auto f = [cnt]() mutable { return ++cnt; };
    auto g = f;
    std::cout << f() << f() << g();
    return 0;
}
```

A. 121
B. 123
C. 111
D. 编译错误

---

**解析：**

`mutable` 使 lambda 的值捕获变量可被修改，每次调用会修改 lambda 对象内部的拷贝。但 lambda 的 `operator()` 是**非 const**，因此 `auto g = f` 触发生成 lambda 的拷贝构造函数——`g` 拿到了 `f` 中 `cnt` 的快照（值为 0）。然后：`f()` 使 f 的 cnt 从 0→1，返回 1；再次 `f()` 从 1→2，返回 2；`g()` 从 0→1，返回 1。输出 121。