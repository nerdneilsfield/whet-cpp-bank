---
qid: cpp-io-med-003
type: single
kp: [cpp-io]
difficulty: medium
answer_key: D
---

`std::stringstream` 的类型转换使用不当会造成意想不到的结果。以下代码输出是？

```cpp
#include <sstream>
#include <iostream>

int main() {
    std::stringstream ss;
    ss << "42abc";
    int x;
    ss >> x;
    std::cout << "x=" << x << " fail=" << std::boolalpha << ss.fail();
}
```

A. `x=42 fail=false`（读取到非数字字符前停止）
B. `x=0 fail=true`（非数字导致读取失败）
C. `x=42 fail=true`（部分读取成功但未读完全部输入）
D. `x=42 fail=false`（只读取了 `42`，`abc` 留在流中）

---

**解析：**

`operator>>(int&)` 的行为是：跳过前导空白，读取尽可能多的数字字符直到遇到非数字字符，然后尝试将读取的字符序列转换为 `int`。如果至少有一个数字被读取，则成功（`failbit` 不置位），剩余的 `abc` 留在流中等待后续读取。

所以 `x` 被赋值 `42`，流状态正常（`fail()` 为 `false`）。如果输入流没有任何数字（如 `"abc"`），则读取失败，`failbit` 被置位，`x` 不修改（C++11+）。

这个陷阱常见于"检查输入合法性"场景——只检查 `!fail()` 是不够的，因为部分解析也算成功。

## Explanation

正确答案是 D，对应“x=42 fail=false（只读取了 42，abc 留在流中）”。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。其他选项容易混淆相关概念：A 项“x=42 fail=false（读取到非数字字符前停止）”不满足题干要求；B 项“x=0 fail=true（非数字导致读取失败）”不满足题干要求；C 项“x=42 fail=true（部分读取成功但未读完全部输入）”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
