---
qid: cpp-cross-ec-005
type: single
kp: [cpp-enum, cpp-casting, cpp-control-flow]
difficulty: easy
answer_key: B
---

以下代码输出是什么？

```cpp
#include <iostream>

struct Animal  { virtual ~Animal() {} };
struct Dog : Animal {};
struct Cat : Animal {};

void identify(Animal* p) {
    if (dynamic_cast<Dog*>(p) != nullptr) {
        std::cout << "dog\n";
    } else if (dynamic_cast<Cat*>(p) != nullptr) {
        std::cout << "cat\n";
    } else {
        std::cout << "other\n";
    }
}

int main() {
    Animal* a = new Cat();
    identify(a);
    delete a;
    return 0;
}
```

A. `dog`  
B. `cat`  
C. `other`  
D. 运行时崩溃，`dynamic_cast` 对基类指针无效

<!--
a 实际指向 Cat 对象。
dynamic_cast<Dog*>(a) 转换失败，返回 nullptr，第一个 if 为假。
dynamic_cast<Cat*>(a) 转换成功，返回非空指针，第二个 if 为真。
输出 "cat"。
基类 Animal 有虚析构函数，dynamic_cast 可正常工作。
-->

## Explanation

B 正确：`a` 的动态类型是 `Cat`，所以 `dynamic_cast<Dog*>(a)` 返回空指针，而 `dynamic_cast<Cat*>(a)` 成功。`Animal` 有虚析构函数，类型是多态类型，指针形式的 `dynamic_cast` 合法且失败时返回 `nullptr`。关键误区是认为基类指针不能做运行时向下转换。
