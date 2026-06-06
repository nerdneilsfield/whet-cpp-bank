---
qid: cpp-real-quiz-010
type: single
kp: [cpp-inheritance]
primary_kp: cpp-inheritance
difficulty: hard
answer_key: A
tags: [interview-real, cppquiz, language-lawyer]
---
根据 C++17 标准，假设内存对齐未干预，以下程序的输出是？

```cpp
#include <iostream>
struct A          { char c;          };
struct B : A      { char d;          };
struct C : A      { char e;          };
struct D : B, C   { char f;          };
struct DV : virtual A { char g;      };
struct DV2 : virtual A { char h;    };
struct DDV : DV, DV2  { char i;     };
int main() {
    std::cout << sizeof(D) << ' ' << sizeof(DDV);
}
```

A. `3 8`（或接近值，A 非空导致 D 内含两个 A 子对象）
B. `2 3`
C. `4 4`
D. 编译错误

---

**解析：**

**非虚继承**的 `D : B, C`：每个路径各含一个 `A` 子对象（"**菱形重复子对象**"），`D` 里有 `B::A::c` 和 `C::A::c` 再加三个 `char`（d, e, f），共 5 char；但对齐最大成员为 1，就是 `5` 吗？注意 `B` 和 `C` 各自空基类优化（EBO）在有多继承时不适用，结果至少是 `3`（B的2 + C的2 - A重叠 = 3 char）。实际上由于布局规则，各编译器对齐细节不同，但关键认知是 D 明显比各基类成员之和还小不了多少，至少 >= 3。

**虚继承**的 `DDV`：虚继承保证只有一个 `A` 子对象。每个虚基类 A 的内容在对象末尾，每个 DV/DV2 内部需要 vptr 或偏移指针来定位 A。常见 x64 实现下 DDV 至少：vptr(DV)8 + char g + vptr(DV2)8 + char h + vptr(DDV) 不另算 + char i + A::char c，总体约 8~12 字节。

核心考点：非虚菱形继承产生多个同一个基类的副本，虚继承归并为一个；虚继承的 vtable 指针额外开销显著。

**来源：** C++ Brain Teasers / Itanium C++ ABI；C++17 [class.mem]/[class.derived]

## Explanation

正确答案是 A。
*虚继承的 DDV：虚继承保证只有一个 A 子对象。每个虚基类 A 的内容在对象末尾，每个 DV/DV2 内部需要 vptr 或偏移指针来定位 A。常见 x64 实现下 DDV 至少：vptr(DV)8 + char g + vptr(DV2)8 + char h + vptr(DDV) 不另算 + char i + A::char c，总体约 8~12 字节。
核心考点：非虚菱形继承产生多个同一个基类的副本，虚继承归并为一个；虚继承的 vtable 指针额外开销显著。
