---
qid: cpp-stl-adv-006
type: fill
kp: [cpp-stl-basics]
difficulty: easy
answer_key: 1
---

# std::sort 对 std::array 排序后的首元素

```cpp
#include <array>
#include <algorithm>
#include <iostream>

int main() {
    std::array<int, 5> arr = {3, 1, 4, 1, 5};
    std::sort(arr.begin(), arr.end());
    std::cout << arr[0] << std::endl;
    return 0;
}
```

上述代码输出什么？填写具体数值：___

> **知识点**：`std::sort(arr.begin(), arr.end())` 对 `std::array` 原地升序排序（默认 `operator<`）。排序后数组为 `{1, 1, 3, 4, 5}`，`arr[0]` 为最小值 `1`。
