---
qid: cpp-enum-012
type: single
kp: [cpp-enum]
difficulty: easy
answer_key: C
---
以下 switch 代码的输出是什么？

```cpp
#include <iostream>
enum class Season { Spring, Summer, Autumn, Winter };
int main() {
    Season s = Season::Autumn;
    switch (s) {
        case Season::Spring:  std::cout << "S"; break;
        case Season::Summer:  std::cout << "U"; break;
        case Season::Autumn:  std::cout << "A"; break;
        case Season::Winter:  std::cout << "W"; break;
    }
}
```

A. S
B. U
C. A
D. W
