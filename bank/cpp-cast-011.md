---
qid: cpp-cast-011
type: fill
kp: [cpp-casting]
difficulty: easy
answer_key: "编译错误（不能用 static_cast 去除 const）"
---

# static_cast 去 const

```cpp
const int ci = 42;
int* p = static_cast<int*>(&ci);  // 此行
```

上述代码（"此行"）会发生什么？___

## Explanation

答案是编译错误。`static_cast` 不能去除 `const` 限定，`const int*` 到 `int*` 的转换必须显式使用 `const_cast`。即使用 `const_cast` 编译通过，若原对象本身为 const，再写入仍是未定义行为。
