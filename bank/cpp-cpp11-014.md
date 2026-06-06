---
qid: cpp-cpp11-014
type: single
kp: [cpp-cpp11]
difficulty: easy
answer_key: B
---

# 代码阅读：= delete 阻止拷贝

以下代码能否编译通过？

```cpp
struct NoCopy {
    NoCopy() = default;
    NoCopy(const NoCopy&) = delete;
};

int main() {
    NoCopy a;
    NoCopy b = a;  // 此行
}
```

A. 可以编译，`b` 是 `a` 的拷贝
B. 编译失败，拷贝构造函数已被删除
C. 编译成功，但运行时崩溃
D. 编译成功，`b` 与 `a` 是同一对象
