---
qid: cpp-cast-009
type: fill
kp: [cpp-casting]
difficulty: easy
answer_key: "3"
---

# static_cast 截断行为

```cpp
#include <iostream>
int main() {
    double x = 3.9;
    int y = static_cast<int>(x);
    std::cout << y;
}
```

程序输出是：___

## 解析

答案是 `3`。题干要求填写的是能直接满足语法、命令或代码执行结果的精确文本，其他近似写法通常会改变含义或无法通过严格匹配。常见误区是把相关概念写成解释性短语，或忽略空格、符号、大小写等细节。类型转换题要区分编译期转换、运行期检查、cv 限定和底层位模式重解释。
