---
qid: cpp-cast-010
type: fill
kp: [cpp-casting]
difficulty: easy
answer_key: "nullptr（空指针）"
---

# dynamic_cast 向下转型失败

```cpp
#include <iostream>
struct Base { virtual ~Base() {} };
struct Derived : Base {};
struct Other  : Base {};

int main() {
    Base* b = new Derived();
    Other* o = dynamic_cast<Other*>(b);
    std::cout << (o == nullptr ? "nullptr" : "非空");
}
```

程序输出是：___

## Explanation

答案是 `nullptr（空指针）`。题干要求填写的是能直接满足语法、命令或代码执行结果的精确文本，其他近似写法通常会改变含义或无法通过严格匹配。常见误区是把相关概念写成解释性短语，或忽略空格、符号、大小写等细节。类型转换题要区分编译期转换、运行期检查、cv 限定和底层位模式重解释。
