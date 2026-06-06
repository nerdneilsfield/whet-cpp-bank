---
qid: cpp-scope-020
type: fill
kp: [cpp-scope-linkage]
difficulty: easy
answer_key: "编译错误"
---

# const 成员函数修改普通成员

阅读以下代码：

```cpp
struct Foo {
    int value = 0;

    void set(int v) const {
        value = v;  // 这行
    }
};

int main() {
    Foo f;
    f.set(42);
    return 0;
}
```

编译该代码会产生什么结果？

答：______ （填"正常编译"或"编译错误"）

> 提示：`const` 成员函数不允许修改未标记 `mutable` 的成员变量。
