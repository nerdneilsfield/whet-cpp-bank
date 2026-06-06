---
qid: cpp-cast-013
type: fill
kp: [cpp-casting]
difficulty: easy
answer_key: "42（成功向下转型）"
---

# dynamic_cast 成功向下转型

```cpp
#include <iostream>
struct Animal { virtual ~Animal() {} };
struct Dog : Animal { int id = 42; };

int main() {
    Animal* a = new Dog();
    Dog* d = dynamic_cast<Dog*>(a);
    if (d) std::cout << d->id;
    else   std::cout << "失败";
}
```

程序输出是：___

## Explanation

答案是 `42（成功向下转型）`。题干要求填写的是能直接满足语法、命令或代码执行结果的精确文本，其他近似写法通常会改变含义或无法通过严格匹配。常见误区是把相关概念写成解释性短语，或忽略空格、符号、大小写等细节。类型转换题要区分编译期转换、运行期检查、cv 限定和底层位模式重解释。
