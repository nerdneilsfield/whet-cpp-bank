---
qid: cpp-cpp11-r-003
type: single
kp: [cpp-cpp11]
difficulty: easy
answer_key: "D"
---

### 题目

阅读以下代码，编译结果是什么？

```cpp
struct NoCopy {
    NoCopy() = default;
    NoCopy(const NoCopy&) = delete;
    NoCopy& operator=(const NoCopy&) = delete;
};

int main() {
    NoCopy a;
    NoCopy b = a;  // 行 A
    NoCopy c;
    c = a;         // 行 B
}
```

A. 编译通过，运行正常
B. 仅行 A 处编译错误
C. 仅行 B 处编译错误
D. 行 A 和行 B 均编译错误

## Explanation

正确答案是 D。`= delete` 明确禁用某个函数，误用会在编译期报错而不是运行期失败。选项 D 的表述“行 A 和行 B 均编译错误”正好符合该规则。A、B、C 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。 进一步判断时要回到题干给出的具体代码、接口名和标准语义，避免用相似概念的经验结论替代本题要求。
