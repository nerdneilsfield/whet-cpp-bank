---
qid: cpp-stl-med-003
type: single
kp: [cpp-stl-basics]
difficulty: medium
answer_key: C
---
下列代码中的 `v` 处于什么状态？

```cpp
#include <string_view>
#include <iostream>
std::string_view get_view() {
    std::string s = "hello, world!";
    return s;
}
int main() {
    std::string_view v = get_view();
    std::cout << v[0];
    return 0;
}
```

A. 输出 'h'，完全安全
B. 编译错误：返回 `string_view` 不能绑定到局部 `string`
C. 悬垂指针：`v` 指向已被析构的 `s` 的内部缓冲区
D. `string_view` 自动复制字符串内容，因此安全

---

**解析：**

`std::string_view` 是不拥有所有权的视图：它仅保存指向字符数据的指针和长度，不管理内存。`get_view()` 中 `s` 是局部变量，函数返回时被析构，其缓冲区被释放。返回的 `string_view` 依然持有一个指向已释放内存的指针，构成悬垂指针。在 `main` 中访问 `v[0]` 是 UB。`string_view` 永远只是“看一眼”，不应持有比底层字符串更长的生命周期。