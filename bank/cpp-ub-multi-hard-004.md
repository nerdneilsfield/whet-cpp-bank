---
qid: cpp-ub-multi-hard-004
type: multi
kp: [cpp-undefined-behavior]
difficulty: hard
answer_key: [A, B, C]
---
关于 C++17 之前的 sequence point 规则与 C++17 之后的 sequenced-before 关系，以下说法正确的是哪些？

```cpp
int i = 0;
i = i++;                // (1)
i = ++i + i++;          // (2)

int arr[3] = {0};
arr[i] = i++;           // (3)
int x = i++ + i++;      // (4)
```

A. (1) 在 C++17 之前是 UB（两次 side effect 写同一变量之间无 sequence point），C++17 之后（i++ 的值计算 sequenced-before i= 的副作用）变成定义良好——等价于 `i = 0; i += 1;`。
B. (4) 即使在 C++17 之后依然是 UB——因为一个表达式包含对 `i` 的两次未排序（unsequenced）增量修改（`i++` 的副作用与另一个 `i++` 之间无顺序）。
C. (3) `arr[i] = i++`：C++17 中下标表达式的值计算和 `i++` 的副作用相对于赋值操作符是 sequenced-before 的，所以先读 `i` 然后写 `arr[i]` 再 `i++`，定义良好。
D. (2) 在 C++17 下完全合法——虽然表达式复杂但有确定的求值顺序。

---

**解析：**

A 正确：C++17 引入的求值顺序规则规定赋值 `=` 右侧表达式的值计算 sequenced-before 左侧；`i = i++` 先读 `i`（0），再赋予 `i`，然后 `i++` 自增。整体结果 `i = 1`，不再 UB。

B 正确：`i++ + i++` 中对 `i` 两次增量（两个 `i++` 的副作用）是**同一表达式**内对同一变量的两次未排序修改，无论 C++ 版本都是 UB。C++17 只改变了赋值左右侧的关系，不影响这里。

C 正确：C++17 修改了规则确保 `a[b] = expr` 中 `a` 和 `b` 的值计算 sequenced-before 赋值，而 `expr` 的值计算也 sequenced-before 赋值。但对 `arr[i] = i++`：`i` 的值计算（在 `arr[i]` 中）sequenced-before 赋值，`i++` 的值计算同样 sequenced-before 赋值，两者间未排序但并非修改同一变量。故定义良好。

D 错误：即使 C++17，`(++i) + (i++)` 中两个增量操作（`++i` 修改和 `i++` 修改）是**unsequenced**的，同时修改同一变量仍是 UB。C++17 只修复了赋值相关的求值顺序，未修复此类表达式的顺序问题。

## Explanation

A、B、C 正确：C++17 对赋值相关求值顺序作了调整，使部分旧表达式不再 UB，但没有给所有子表达式都规定顺序。两个 `i++` 或 `++i` 与 `i++` 在加法两侧仍是未排序地修改同一标量，依然 UB。常见误区是以为 C++17 彻底解决了所有 sequence point 问题。
