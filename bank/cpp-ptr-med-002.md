---
qid: cpp-ptr-med-002
type: single
kp: [cpp-arrays-pointers]
difficulty: medium
answer_key: C
---
下列关于 `void*` 指针运算的说法，正确的是？

```cpp
void* p = /* ... */;
p = p + 1;        // (a)
sizeof(*p);       // (b)
```

A. (a)、(b) 都合法
B. (a) 合法，(b) 不合法
C. (a)、(b) 都不合法（标准 C++）
D. (a) 不合法，(b) 合法

---

**解析：**

标准 C++ 禁止对 `void*` 做算术运算，因为 `void` 是不完整类型，没有“元素大小”可用，编译器不知道 `+1` 应推进多少字节。同理 `sizeof(void)` 和 `sizeof(*p)`（解引用 `void*` 得到 `void`）都是不合法的，因为 `void` 没有大小。GCC 作为扩展把 `void*` 算术按 1 字节处理，但这是非标准的；可移植代码应先转换为具体类型指针（如 `char*`）再做运算。
