---
qid: cpp-cpp11-med-002
type: single
kp: [cpp-cpp11]
difficulty: medium
answer_key: C
---

下列代码的输出是？

```cpp
#include <vector>
#include <iostream>

struct BoolProxy {
    bool val;
    explicit operator bool() const { return val; }
};

struct Container {
    BoolProxy operator[](size_t) const { return {true}; }
    size_t size() const { return 5; }
    struct Iter {
        size_t i;
        bool operator!=(Iter o) const { return i != o.i; }
        BoolProxy operator*() const { return {true}; }
        Iter& operator++() { ++i; return *this; }
    };
    Iter begin() const { return {0}; }
    Iter end() const { return {size()}; }
};

int main() {
    Container c;
    for (auto x : c) {
        std::cout << typeid(x).name() << ' ';
        break;
    }
}
```

A. 编译失败，因为 `auto` 无法推导 `BoolProxy`
B. 输出 `b`（`bool` 类型），隐含调用 `operator bool()`
C. 输出 `9BoolProxy`，`x` 保留为 `BoolProxy` 类型
D. 未定义行为

---

**解析：**

`range-for` 展开为 `auto __begin = c.begin(); auto __end = c.end(); __begin != __end; ++__begin`，其中 `auto x = *__begin;`。`x` 的类型是 `BoolProxy`（值类型），不会隐式转换到 `bool`。标准中的 `auto` 展开就是模板式推导，不会添加隐式转换。

这个陷阱常出现在 STL 的 `vector<bool>` 中，其 `operator[]` 返回 `__Bit_reference` 代理对象而非 `bool&`，`auto` 推导出代理类型而不是 `bool`。