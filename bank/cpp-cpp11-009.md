---
qid: cpp-cpp11-009
type: fill
kp: [cpp-cpp11]
difficulty: easy
answer_key: "nullptr"
---

# 代码阅读：nullptr 替代 NULL

阅读以下代码，填入空白处使其通过编译且类型安全：

```cpp
void foo(int* p) {}
void foo(int n)  {}

int main() {
    foo(______);  // 应调用指针版本，而非整数版本
}
```

空白处应填写：___

## Explanation

应填 `nullptr`。`nullptr` 的类型是 `std::nullptr_t`，它不会像 `NULL` 那样被当作整数参与重载解析。 这个答案对应题干要求的标准名称、成员函数或复杂度写法。常见误区是填写相近但语义不同的接口，或漏掉作用域、大小写、下划线等精确拼写要求。
