---
qid: cpp-stl-adv-014
type: fill
kp: [cpp-stl-basics]
difficulty: easy
answer_key: txt
---

# 用 rfind 提取文件扩展名

```cpp
#include <string>
#include <iostream>

int main() {
    std::string filename = "report.final.txt";
    auto dot_pos = filename.rfind('.');
    std::string ext = filename.substr(dot_pos + 1);
    std::cout << ext << std::endl;
    return 0;
}
```

上述代码输出什么？填写具体字符串：___

> **知识点**：`rfind('.')` 找到最后一个 `'.'` 的位置（下标 12），`substr(dot_pos + 1)` 从下一个字符到末尾，得到扩展名 `"txt"`。用 `rfind` 而非 `find` 是为了正确处理带多个点的文件名（如 `report.final.txt`）。
