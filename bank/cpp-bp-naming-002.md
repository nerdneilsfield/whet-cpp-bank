---
qid: cpp-bp-naming-002
type: single
kp: [cpp-scope-linkage]
difficulty: medium
answer_key: C
---

以下头文件的最大问题是什么？

```cpp
// my_lib.h
#pragma once
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace mylib {
    vector<string> split(const string& s, char c);
}
```

A. #pragma once 不可移植
B. 应该包含 <vector> 之前包含 <string>
C. 头文件中 using namespace std 污染所有包含者的全局命名空间，可能引起 ADL 冲突
D. 函数应该用尾置返回类型

---

## 解析

**头文件中 `using namespace std;`（或任何 namespace）是 C++ 最严重的命名空间反模式之一**。

危害：
1. **传染性**：任何包含 `my_lib.h` 的 .cpp 文件（甚至间接包含）都会被注入 `using namespace std;`。一个头被几百个 TU 包含 = 几百个 TU 被污染。
2. **难以诊断的冲突**：用户写 `vector<int>` 突然莫名编译失败，发现是因为某个第三方头注入了同名类型的另一个命名空间。
3. **ADL 陷阱**：很多函数（如 `swap`、`begin`、`end`）依赖 ADL 找到正确版本。`using namespace std` 让 std 版本和用户版本都可见，重载解析变成噩梦。
4. **未来不兼容**：C++ 标准每个版本都加新名字。`std::data`（C++17）、`std::erase`（C++20）等加入后，可能与用户代码已有的 `data` / `erase` 冲突。

**规则**：
- 头文件中**永远不要** `using namespace`
- 函数实现 .cpp 文件中可接受，但仍推荐**局部 using**：

```cpp
// 推荐
namespace mylib {
    std::vector<std::string> split(const std::string& s, char c);
}
```

```cpp
// .cpp 中可接受的局部 using
void some_function() {
    using std::vector;          // 局部，仅函数内
    using std::string;
    vector<string> result;
}
```

正确答案 C。