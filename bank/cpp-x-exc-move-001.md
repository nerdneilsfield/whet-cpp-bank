---
qid: cpp-x-exc-move-001
type: single
kp: [cpp-exceptions, cpp-move-semantics]
primary_kp: cpp-exceptions
difficulty: medium
answer_key: A
---

`vector<T>` 在 `push_back` 触发扩容时，保证要么成功要么回到原始状态（strong exception guarantee）。此保证依赖于以下哪个条件？

```cpp
#include <vector>
#include <string>

struct Container {
    std::vector<int> v;
    // 假设此处不主动声明移动构造函数
};

int main() {
    std::vector<Container> vec(3);  // 已存储 3 个元素
    // 如果下面 push_back 引起扩容，是否安全？
    vec.push_back(Container{});
}
```

A. 需要 `Container` 的移动构造函数标记为 `noexcept`，否则 vector 会拷贝而非移动
B. 移动构造函数必须是 `= default` 的，否则 vector 退化为拷贝
C. vector 总是直接移动，与 noexcept 无关
D. 只要 `Container` 有复制构造函数，就一定能回滚

---

## 解析

[vector.modifiers]/1：`vector` 在重新分配时使用移动构造函数，**当且仅当**移动构造函数是无异常声明（`noexcept` 或 `noexcept(true)`）时。

原因是 strong exception guarantee 的要求：如果移动操作可能抛异常，vector 重新分配时若把旧元素移动到新内存后异常抛出，旧缓冲区里已被移走的元素无法被恢复，导致容器状态不一致。因此标准库退化为 **拷贝构造**——拷贝失败时旧缓冲区保持不变，exception safety 得以保证。

- **A 对**：如果没有 `noexcept` 移动构造，vector 用拷贝构造（即使移动构造可用）。
- **B 错**：`= default` 并不自带 noexcept——编译器是否隐式加 noexcept 取决于成员的移动操作是否 noexcept。此处 `Container` 的成员 `std::vector<int>` 的移动是 noexcept 的，所以 `= default` 的移动构造也会隐式 noexcept；但若依赖隐式生成则此点正确，不过 B 的表述「必须 = default」太绝对，显式 `= default` 或 `= delete` 均可。
- **C 错**：与 noexcept 严格相关。
- **D 错**：有复制构造也不能保证回滚——如果同时有抛异常的移动构造，vector 优先选择移动构造（因非 noexcept 而不安全），这才是危险所在。