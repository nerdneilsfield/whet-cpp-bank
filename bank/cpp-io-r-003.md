---
qid: cpp-io-r-003
type: single
kp: [cpp-io]
difficulty: easy
answer_key: "C"
---

### 题目

假设文件 `data.txt` 初始内容为 `AAA`。运行以下代码后，文件内容是什么？

```cpp
#include <fstream>

int main() {
    std::ofstream f("data.txt", std::ios::app);
    f << "BBB";
}
```

A. `BBB`
B. `BBBAAA`
C. `AAABBB`
D. 文件被清空，内容为空

## Explanation

`std::ios::app`（追加模式）每次写操作前将写位置移到文件末尾，不会截断已有内容。因此 `"BBB"` 追加在 `"AAA"` 之后，文件内容变为 `"AAABBB"`。若改用默认的 `std::ios::out`（即不指定任何模式），文件会被截断后重新写入。
