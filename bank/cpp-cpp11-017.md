---
qid: cpp-cpp11-017
type: multi
kp: [cpp-cpp11]
difficulty: easy
answer_key: [A, C, D]
---

# 代码阅读：统一初始化的合法用法

以下哪些初始化写法在 C++11 中**合法且不触发窄化转换错误**？（多选）

```cpp
A. int a{42};
B. int b{3.14};
C. std::vector<int> v{1, 2, 3};
D. double d{42};
E. char c{300};
```

选出所有合法的选项：

## Explanation

正确答案是 A、C、D。花括号列表初始化会禁止窄化转换，这是 C++11 统一初始化的重要安全性。 A 正确：int a{42};；B 错误：int b{3.14};；C 正确：std::vector<int> v{1, 2, 3};；D 正确：double d{42};；E 错误：char c{300}; ｀｀｀ 选出所有合法的选项：。常见误区是只记住术语名称，而忽略每个选项中的限定条件、生命周期、同步关系或复杂度前提。
