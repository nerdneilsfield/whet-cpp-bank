---
qid: cpp-ub-multi-hard-005
type: multi
kp: [cpp-undefined-behavior]
difficulty: hard
answer_key: [A, B, D]
---
关于读取未初始化值，以下说法正确的是哪些？

```cpp
int main() {
    int x;                          // (1) 未初始化
    int y = x + 1;                  // (2)

    unsigned char buf[16];           // (3)
    unsigned char b = buf[0];        // (4)
    int z;
    unsigned char* p = reinterpret_cast<unsigned char*>(&z);
    unsigned char b2 = p[0];         // (5)
}
```

A. (1) 中 `x` 含有 indeterminate value（不确定值）；(2) 读取此值用于算术是 UB（因为可能含有 trap representation）。
B. (3)(4) 中 `unsigned char` 类型对象的读取**不会** UB——`unsigned char` 不存在 trap representation，未初始化值合法读取（但内容不可预测）。
C. (5) 通过 `unsigned char*` 访问未初始化的 `int z`，根据"字符类型例外"和"无 trap representation"规则，绝对安全，且能可靠读出 `z` 的字节模式。
D. C++14 起 indeterminate value 的概念明确化：读取自动存储期对象的未初始化值（非 `unsigned char/std::byte` 类型）是 UB；编译器可基于此做激进优化（例如把整个分支判定优化掉）。

---

**解析：**

A 正确：标准 [dcl.init]/12 规定未初始化的自动对象具有 indeterminate value，对其求值（非 `unsigned char` 等例外情况）是 UB；可能包含 trap representation 在某些架构上一旦读取就触发异常。

B 正确：`unsigned char` 和（C++17 起）`std::byte` 类型本身没有 trap representation，对它们读取未初始化值是已定义行为，得到 "unspecified value"，可以读但内容不确定。

C 错误：CWG defect 1787 与后续澄清表明，即使通过 `unsigned char*` 别名访问，**如果该底层存储中存放的是其他类型的未初始化对象（如 `int z`）**，访问其字节仍可能是 UB（编译器视该读为"用了 indeterminate value"）。规则更细致：若该 `int` 已被初始化或通过 `memcpy` 写入，则可读其字节；纯未初始化的非 char 对象按字节读仍 UB。

D 正确：C++14 起明确：indeterminate value 的使用是 UB（除少数例外）。Clang/GCC 利用此 UB 做激进优化，"if (uninit_var) ..." 整个分支可被消除，导致看似神秘的 bug。`-Wuninitialized` 与 sanitizer 是常用检测手段。

## Explanation

A、B、D 正确：普通自动变量未初始化后的值是 indeterminate value，参与算术等求值属于未定义行为，而 `unsigned char` 作为例外类型读取自身未初始化值不会因 trap representation 触发 UB。关键点是“字符类型例外”并不等于可以任意安全观察其他未初始化对象的对象表示。常见误区是把 `unsigned char*` 能别名任意对象，误解成能读取未开始有效值语义的任意未初始化对象。
