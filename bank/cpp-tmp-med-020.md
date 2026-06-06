---
qid: cpp-tmp-med-020
type: single
kp: [cpp-templates]
difficulty: medium
answer_key: A
---

以下模板递归实现编译期阶乘：

```cpp
#include <type_traits>

template<int N>
struct Factorial {
    static constexpr int value = N * Factorial<N - 1>::value;
};

template<>
struct Factorial<0> {
    static constexpr int value = 1;
};

static_assert(Factorial<5>::value == 120, "Factorial<5> should be 120");
```

`static_assert` 能否通过？

A. 能通过，`Factorial<5>::value` 在编译期递归展开为 120
B. 不能通过，模板递归不能用于编译期计算
C. 编译错误：没有递归终止条件
D. 能通过，但只在运行期求值，`static_assert` 不检查

---

**解析：**

模板递归展开过程：  
`Factorial<5>::value` = 5 × `Factorial<4>::value`  
= 5 × 4 × `Factorial<3>::value`  
= …  
= 5 × 4 × 3 × 2 × 1 × `Factorial<0>::value`  
= 5 × 4 × 3 × 2 × 1 × 1  
= **120**

全特化 `Factorial<0>` 提供递归终止。整个求值在**编译期**完成，`static_assert` 在编译期断言，通过。  
这是 C++ 编译期计算的经典示例，也是 `constexpr` 函数发明之前的主流写法。
