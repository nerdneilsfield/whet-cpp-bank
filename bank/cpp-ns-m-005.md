---
qid: cpp-ns-m-005
type: multi
kp: [cpp-preprocessor]
difficulty: easy
answer_key: [A, C, D]
---

关于在头文件中写 `using namespace std;`，下列哪些说法**正确**？（选择所有正确项）

A. 所有 `#include` 该头文件的翻译单元都会被污染，无法选择退出
B. 仅在该头文件自身的作用域内有效，不影响包含它的文件
C. 可能导致与用户自定义名称发生冲突，引发难以排查的歧义错误
D. 推荐做法是在头文件中使用完整限定名（如 `std::string`）而非 `using namespace std`

