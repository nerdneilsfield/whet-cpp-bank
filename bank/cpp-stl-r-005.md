---
qid: cpp-stl-r-005
type: single
kp: [cpp-stl-basics]
difficulty: easy
answer_key: B
---

# 代码阅读：std::sort 不能用于 list

下列代码能否编译？

```cpp
#include <list>
#include <algorithm>

int main() {
    std::list<int> lst = {3, 1, 4, 1, 5};
    std::sort(lst.begin(), lst.end()); // 对 list 排序
}
```

A. 能编译，`std::sort` 对所有容器的迭代器均有效  
B. 编译错误：`std::sort` 要求随机访问迭代器，`std::list` 的迭代器只是双向迭代器  
C. 能编译，但排序结果未定义  
D. 能编译，`std::sort` 会自动检测迭代器类型并降级为插入排序
