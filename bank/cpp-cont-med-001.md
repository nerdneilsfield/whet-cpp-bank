---
qid: cpp-cont-med-001
type: single
kp: [cpp-containers]
difficulty: medium
answer_key: C
---
下列代码执行后，`m.size()` 是？

```cpp
#include <map>
#include <iostream>
int main() {
    std::map<int, int> m;
    if (m[42] == 0) {
        std::cout << "yes";
    }
    std::cout << " size=" << m.size();
    return 0;
}
```

A. 0
B. 输出 "yes" 但 size=0
C. 输出 "yes size=1"
D. 编译错误

---

**解析：**

`std::map::operator[]` 是“查找或默认插入”：当 key 不存在时，会用值类型的默认构造函数插入一个新元素并返回它的引用。这里 `m[42]` 触发插入一对 `{42, 0}`（`int` 默认初始化为 0），再读取得到 `0`，条件成立打印 `yes`。此时 `m.size()` 已变成 1。要避免“只读”但被意外插入，应使用 `m.find(42)` 或 C++20 的 `m.contains(42)`。这是 `map` 使用中最常见的副作用陷阱。

## 解析

正确答案是 C。`std::map` 通常由平衡二叉搜索树实现，键有序，查找/插入/删除为 O(log n)。选项 C 的表述“输出 "yes size=1"”正好符合该规则。A、B、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
