---
qid: cpp-cont-012
type: single
kp: [cpp-containers]
difficulty: easy
answer_key: B
---

阅读以下代码，输出是什么？

```cpp
#include <map>
#include <iostream>
int main() {
    std::map<std::string, int> m;
    std::cout << m["x"] << std::endl;
    std::cout << m.size() << std::endl;
}
```

A. `0` 然后 `0`
B. `0` 然后 `1`
C. 运行时错误
D. 编译错误

## Explanation

正确答案是 B。`std::map` 通常由平衡二叉搜索树实现，键有序，查找/插入/删除为 O(log n)。选项 B 的表述“｀0｀ 然后 ｀1｀”正好符合该规则。A、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
