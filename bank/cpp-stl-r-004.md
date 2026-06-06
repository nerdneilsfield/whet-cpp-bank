---
qid: cpp-stl-r-004
type: single
kp: [cpp-stl-basics]
difficulty: easy
answer_key: C
---

# 代码阅读：map operator[] 对不存在的 key 插入默认值

下列代码输出什么？

```cpp
#include <map>
#include <iostream>

int main() {
    std::map<std::string, int> m;
    m["a"] = 1;
    std::cout << m["b"] << std::endl;  // "b" 不存在
    std::cout << m.size() << std::endl;
}
```

A. 运行时抛出 `std::out_of_range` 异常  
B. 输出 `0` 和 `1`（`size` 不变，仅读取默认值）  
C. 输出 `0` 和 `2`（`operator[]` 插入了键 `"b"`，值默认初始化为 `0`）  
D. 编译错误：`map` 下标访问不存在的键是非法的
