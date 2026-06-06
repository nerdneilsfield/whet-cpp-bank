---
qid: cpp-cont-r-002
type: single
kp: [cpp-containers]
difficulty: easy
answer_key: "B"
---

### 题目

以下代码输出什么？

```cpp
#include <map>
#include <iostream>

int main() {
    std::map<std::string, int> m;
    m["a"] = 1;
    m["b"] = 2;
    std::cout << m.size() << std::endl;
    int x = m["c"];  // "c" 不存在
    std::cout << m.size() << std::endl;
    std::cout << x << std::endl;
}
```

A. `2` / `2` / `0`
B. `2` / `3` / `0`
C. `2` / `2` / 未定义行为
D. 编译错误

## Explanation

`std::map::operator[]` 在键不存在时会**插入**该键并对值进行值初始化（`int` 默认为 `0`），然后返回引用。因此访问 `m["c"]` 后 map 大小从 2 变为 3，`x` 的值为 `0`。如果只想查找不插入，应使用 `m.find("c")`。
