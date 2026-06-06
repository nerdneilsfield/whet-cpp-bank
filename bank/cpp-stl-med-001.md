---
qid: cpp-stl-med-001
type: single
kp: [cpp-stl-basics]
difficulty: medium
answer_key: C
---
下列代码可能出现什么问题？

```cpp
#include <vector>
int main() {
    std::vector<int> v{1, 2, 3};
    auto it = v.begin();
    for (int i = 0; i < 1000; ++i) v.push_back(i);
    *it = 42;   // (*)
    return 0;
}
```

A. 编译错误
B. 一定崩溃
C. `it` 可能已失效，`*it = 42` 是未定义行为
D. 没问题，`it` 始终指向第一个元素

---

**解析：**

`std::vector::push_back` 在容量不足时会重新分配内存：把元素拷贝/移动到新缓冲区并释放旧缓冲区。所有指向旧缓冲区的迭代器、指针、引用都会失效，再访问就是 UB——可能崩溃、可能读到垃圾，也可能“看起来正确”。哪怕只有一次扩容也足以让 `it` 变成悬空指针。要安全保留位置，应用下标 `v[0]` 或在所有 `push_back` 完成后再取迭代器；或先 `reserve` 足够容量。
