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
