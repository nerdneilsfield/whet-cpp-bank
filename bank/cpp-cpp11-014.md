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

## 解析

正确答案是 B。`= delete` 明确禁用某个函数，误用会在编译期报错而不是运行期失败。选项 B 的表述“编译失败，拷贝构造函数已被删除”正好符合该规则。A、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
