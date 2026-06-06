---
qid: cpp-cf-med-003
type: single
kp: [cpp-control-flow]
difficulty: medium
answer_key: B
---
下列代码哪一句会导致编译错误？

```cpp
#include <vector>
int main() {
    std::vector<bool> vb{true, false, true};
    for (auto x : vb)  { x = false; }    // (1)
    for (auto& x : vb) { x = false; }    // (2)
    for (bool& x : vb) { x = false; }    // (3)
    return 0;
}
```

A. (1)
B. (3)
C. (2)
D. 都能编译

---

**解析：**

`std::vector<bool>` 是模板特化，为节省空间按位存储，其 `operator[]` 和迭代器解引用返回的是**代理对象**（`std::vector<bool>::reference`），不是真正的 `bool&`。所以 `bool& x : vb` 试图把代理对象绑定到 `bool&` 引用上是非法的（类型不匹配）。而 `auto x` 拷贝代理对象（合法但修改无效）、`auto& x` 绑定到代理引用上（合法且能写回）都没问题。这是 `vector<bool>` 臭名昭著的“伪容器”陷阱。

## Explanation

正确答案为 B，因为“(3)”符合题干所问的 C++ 规则或代码执行结果。A、C、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。控制流题要按条件判断、循环边界、短路求值和跳转语句的实际执行顺序推演。
