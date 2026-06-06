---
qid: cpp-mem-020
type: multi
kp: [cpp-memory-mgmt]
difficulty: easy
answer_key: [B, C, E]
---

# 下列代码片段中，哪些存在内存安全问题？（多选）

```
A:  auto p = std::make_unique<int>(1);
    int* raw = p.get();
    // 仅使用 raw，不 delete，p 仍存活

B:  int* p = new int(3);
    delete p;
    std::cout << *p;   // use-after-free

C:  int* arr = new int[5];
    delete arr;        // 应为 delete[]

D:  std::shared_ptr<int> sp = std::make_shared<int>(9);
    std::weak_ptr<int> wp = sp;
    // 正常使用 wp.lock()

E:  int* p = new int(10);
    p = nullptr;       // 原指针丢失，无法 delete → 内存泄漏
```

A. 片段 A
B. 片段 B
C. 片段 C
D. 片段 D
E. 片段 E

<!--
A — 安全：raw 是借用指针，unique_ptr 仍负责生命周期。
B — use-after-free，UB。
C — delete 释放 new[] 数组，UB。
D — 安全：weak_ptr 正确用法。
E — 泄漏：覆盖 p 前未 delete。
答案：B C E
-->

## 解析

正确答案是 B、C、E。B 在释放后解引用，是 use-after-free；C 用 `delete` 释放 `new[]` 数组，释放形式不匹配；E 覆盖唯一指针值导致无法再释放原对象。A 中 raw 只是借用指针且 `unique_ptr` 仍存活，D 是 `weak_ptr` 的正常用法。
