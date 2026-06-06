---
qid: cpp-ns-011
type: single
kp: [cpp-preprocessor]
difficulty: easy
answer_key: A
---

以下代码中 `std::cout` 属于哪个命名空间？

```cpp
namespace MyApp {
    void greet() {
        std::cout << "hello";
    }
}
```

A. `std`
B. `MyApp`
C. 全局命名空间
D. `MyApp::std`
