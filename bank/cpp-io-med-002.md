---
qid: cpp-io-med-002
type: single
kp: [cpp-io]
difficulty: medium
answer_key: C
---

`std::endl` 和 `'\n'` 的行为差异（除是否为字符外）是什么？

```cpp
#include <iostream>
#include <chrono>

int main() {
    auto t0 = std::chrono::steady_clock::now();
    for (int i = 0; i < 100000; ++i)
        std::cout << "line\n";
    auto t1 = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration<double>(t1 - t0).count() << "s\n";
}
```

A. `'\n'` 不能输出字符串，只能用 `"\n"`，但和 `std::endl` 一样
B. `'\n'` 不会刷新流，输出可能延迟到程序结束
C. `std::endl` 不仅输出换行还调用 `flush()`，`'\n'` 不强制刷新但 `<iostream>` 在绑定 `cout` 到 `cin` 时会自动刷新
D. `'\n'` 在终端模式下自动刷新，重定向到文件时不刷新

---

**解析：**

`std::endl` 等价于 `os.put(os.widen('\n')).flush()`——强制刷新缓冲区，是昂贵的操作。`'\n'`（包括字符串中的 `\n`）只添加换行字符，不强制刷新。

性能差异显著：`100000` 次循环中，`std::endl` 触发 100k 次系统调用（每次 `flush()` 可能调用 `write`），而 `'\n'` 仅在缓冲区满或遇到交互式行缓冲时刷新。实际测速 `std::endl` 可能慢 10-100 倍。

C++ 标准并未要求 `'\n'` 不刷新，只是不要求刷新。在 `cout` 绑定到 `cin` 时，任何输入输出操作前都会刷新 `cout`（tie 机制）。

## Explanation

正确答案是 C，对应“std::endl 不仅输出换行还调用 flush()，'\n' 不强制刷新但 <iostream> 在绑定 cout 到 cin 时会自动刷新”。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。其他选项容易混淆相关概念：A 项“'\n' 不能输出字符串，只能用 "\n"，但和 std::endl 一样”不满足题干要求；B 项“'\n' 不会刷新流，输出可能延迟到程序结束”不满足题干要求；D 项“'\n' 在终端模式下自动刷新，重定向到文件时不刷新”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
