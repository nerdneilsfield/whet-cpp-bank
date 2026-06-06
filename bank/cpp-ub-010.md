---
qid: cpp-ub-010
type: fill
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: 未定义行为
---

# 未初始化变量读取

```cpp
int main() {
    int x;
    int y = x + 1;  // 此行
    return y;
}
```

读取未初始化的局部变量 `x` 属于______（填：编译错误 / 未定义行为 / 实现定义行为 / 合法操作）。
