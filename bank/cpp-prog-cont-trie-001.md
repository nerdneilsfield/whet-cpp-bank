---
qid: cpp-prog-cont-trie-001
type: prog
kp: [cpp-containers]
primary_kp: cpp-containers
difficulty: hard
toolchain: [make]
tests_dir: tests/cpp-prog-cont-trie-001/
---
实现简易 Trie：insert(word)、search(word)、starts_with(prefix)。只考虑小写字母。

## 函数签名
```cpp
// solution.hpp
#pragma once
#include <string>
#include <array>
#include <memory>

class Trie {
public:
    Trie();
    void insert(const std::string& word);
    bool search(const std::string& word) const;
    bool starts_with(const std::string& prefix) const;
private:
    struct Node {
        std::array<std::unique_ptr<Node>, 26> kids;
        bool end = false;
    };
    Node root_;
};
```

## 提示
- 不要修改 tests/ 下的文件
- 在 skeleton/solution.hpp 中实现函数

## 解析
Trie 的每个节点保存 26 个子节点和一个单词结束标记。插入时按字符下标创建缺失节点，最后把 `end` 置为 true；查找前缀时只要路径存在即可。`search` 与 `starts_with` 的区别是前者还要求最后节点的 `end` 为 true，空串边界按测试期望处理根节点即可。
