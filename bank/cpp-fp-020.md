---
qid: cpp-fp-020
type: multi
kp: [cpp-function-pointers]
difficulty: easy
answer_key: [B, C, D]
---

# 代码阅读：综合辨析可调用对象

阅读下列代码片段，判断哪些说法正确？（多选）

```cpp
#include <iostream>
#include <functional>

int square(int x) { return x * x; }

struct Cube {
    int operator()(int x) const { return x * x * x; }
};

int main() {
    // (1) 函数指针
    int (*fp)(int) = square;

    // (2) 函数对象
    Cube cube;

    // (3) 无捕获 lambda 赋给函数指针
    int (*lp)(int) = [](int x) { return x + 1; };

    // (4) std::function 统一存储
    std::function<int(int)> f1 = fp;
    std::function<int(int)> f2 = cube;
    std::function<int(int)> f3 = lp;

    std::cout << fp(3) << cube(2) << lp(4) << f1(3) << f2(2) << f3(4);
}
```

A. 代码无法通过编译，因为 lambda 不能赋给函数指针  
B. 输出为 `988958`  
C. `f1`、`f2`、`f3` 都能合法构造，`std::function` 支持所有三种可调用形式  
D. `fp(3)` 返回 9，`cube(2)` 返回 8，`lp(4)` 返回 5  
E. `std::function<int(int)> f2 = cube` 会编译失败，因为 `Cube` 不是函数指针  
