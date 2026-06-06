---
qid: cpp-stl-adv-008
type: fill
kp: [cpp-stl-basics]
difficulty: easy
answer_key: 8
---

# s.rfind() 从右向左查找

```cpp
#include <string>
#include <iostream>

int main() {
    std::string s = "foo bar foo";
    auto pos = s.rfind("foo");
    std::cout << pos << std::endl;
    return 0;
}
```

上述代码输出什么？填写具体数值：___

> **知识点**：`rfind()` 从字符串末尾向前搜索，返回最后一次出现的位置。字符串 `"foo bar foo"` 中，第一个 `"foo"` 在下标 0，第二个 `"foo"` 在下标 8。`rfind()` 返回最右边的匹配位置 `8`。（下标从0计：f=0,o=1,o=2,' '=3,b=4,a=5,r=6,' '=7,f=8,o=9,o=10）。答案为 8。

## Explanation

填入 `8`，因为题目要求的是该规则下的精确表达或标准名称。STL 题要关注容器语义、迭代器失效、复杂度和算法是否修改原序列；不要把所有容器都按数组模型理解。 常见误区是写出近似说法、旧式写法或省略必要的命名空间/符号，导致与答案含义不完全一致。
