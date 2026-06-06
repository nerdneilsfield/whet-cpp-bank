---
qid: cpp-iter-017
type: fill
kp: [cpp-iterators]
difficulty: easy
answer_key: "1 2 3 4 5"
---

```cpp
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
std::vector<int> src = {1, 2, 3, 4, 5};
std::vector<int> dst;
std::copy(src.begin(), src.end(), std::back_inserter(dst));
for (int x : dst) std::cout << x << " ";
```

程序输出是 ___。
