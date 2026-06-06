---
qid: cpp-stl-adv-015
type: fill
kp: [cpp-stl-basics]
difficulty: easy
answer_key: I love C++
---

# 用 replace 替换子串后输出

```cpp
#include <string>
#include <iostream>

int main() {
    std::string s = "I love Python";
    auto pos = s.find("Python");
    s.replace(pos, 6, "C++");
    std::cout << s << std::endl;
    return 0;
}
```

上述代码输出什么？填写完整字符串：___

> **知识点**：`find("Python")` 返回 7（`"I love "` 后），`replace(7, 6, "C++")` 删除 6 个字符 `"Python"` 并插入 `"C++"`，结果为 `"I love C++"`。`replace` 的替换串长度不必与被替换长度相同。

## Explanation

填入 `I love C++`，因为题目要求的是该规则下的精确表达或标准名称。STL 题要关注容器语义、迭代器失效、复杂度和算法是否修改原序列；不要把所有容器都按数组模型理解。 常见误区是写出近似说法、旧式写法或省略必要的命名空间/符号，导致与答案含义不完全一致。
