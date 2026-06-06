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

## Explanation

二叉树最大深度递归定义为 `1 + max(left_depth, right_depth)`，空指针深度为 0。递归自然覆盖叶子节点，其左右子树深度都为 0，所以叶子深度为 1。注意不要访问空节点成员，深度按节点数而不是边数计算。
