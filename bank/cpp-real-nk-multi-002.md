---
qid: cpp-real-nk-multi-002
type: multi
kp: [cpp-arrays-pointers, cpp-types]
primary_kp: cpp-arrays-pointers
difficulty: medium
answer_key: [A, B, C, D]
tags: [interview-real, nowcoder]
---

下列关于**指针**和**引用**的区别，正确的有：

A. **指针可以为 nullptr，引用必须绑定到一个有效对象**
B. **指针可以重新指向其他对象（除非 const），引用初始化后不能改变绑定**
C. **sizeof(指针) 是机器字长（如 8 字节），sizeof(引用) 通常等于其引用的对象大小**
D. **指针有多级（int**），引用没有多级（int && 是右值引用，不是引用的引用）**

---

**解析：**

A 对：`int& r;` 是非法的，必须 `int& r = obj;`。`int*` 可以是 nullptr。

B 对：
```cpp
int a = 1, b = 2;
int& r = a;
r = b;  // 修改 a 的值（赋值），不是改变 r 的绑定
int* p = &a;
p = &b;  // 改变指针指向
```

C 对：引用在多数实现中是用指针实现的（占指针大小内存），但 sizeof 的语义上 sizeof(int&) = sizeof(int)。这反映了 ABI 实现层和语义层的区别。

D 对：`int **p` 合法（指向指针的指针），但 `int& &r` 非法（不能有引用的引用，C++11 引用折叠规则除外）。`int&&` 是右值引用，是单独类型，不是"引用的引用"。

其他区别：
- 引用没有数组（`int& arr[10]` 非法），但 `int (&arr)[10]` 是数组的引用
- 指针有算术运算，引用没有

**来源：** 牛客网 C++ 指针引用经典面试题 / huihut/interview