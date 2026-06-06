---
qid: cpp-iter-r-005
type: single
kp: [cpp-iterators]
difficulty: easy
answer_key: "B"
---

### 题目

阅读以下代码，`dest` 的内容是什么？

```cpp
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

int main() {
    std::vector<int> src = {1, 2, 3};
    std::vector<int> dest;
    std::copy(src.begin(), src.end(), std::back_inserter(dest));
    for (int x : dest) std::cout << x << " ";
}
```

A. `dest` 为空，`copy` 需要目标容器预先分配空间
B. `1 2 3`
C. 未定义行为，`dest` 未预留空间
D. 编译错误，`back_inserter` 返回类型不兼容 `copy`

## Explanation

`std::back_inserter(dest)` 返回一个 `back_insert_iterator`，每次赋值时调用 `dest.push_back(value)`，因此无需预先 `resize` 或 `reserve`。`std::copy` 将 `src` 的三个元素依次"写入"该迭代器，等效于逐一 `push_back`，最终 `dest` 内容为 `{1, 2, 3}`。
