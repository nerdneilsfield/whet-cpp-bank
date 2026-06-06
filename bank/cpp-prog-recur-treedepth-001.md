---
qid: cpp-prog-recur-treedepth-001
type: prog
kp: [cpp-functions]
primary_kp: cpp-functions
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-recur-treedepth-001/
---
求二叉树最大深度（根到最远叶的节点数）。`nullptr` 返回 0。`Node` 类型如下：

```cpp
struct Node { int val; Node* left; Node* right; Node(int v): val(v), left(nullptr), right(nullptr) {} };
int maxDepth(Node* root);
```