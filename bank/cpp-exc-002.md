---
qid: cpp-exc-002
type: single
kp: [cpp-exceptions]
difficulty: easy
answer_key: C
---

# C++ 异常处理：catch(...) 语法

下列哪个 `catch` 块能捕获**所有类型**的异常？

A. `catch(void)`
B. `catch(any)`
C. `catch(...)`
D. `catch(exception)`

## Explanation

正确答案是 C。`catch(...)` 是兜底处理器，可匹配任意类型的异常。选项 C 的表述“｀catch(...)｀”正好符合该规则。A、B、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。 进一步判断时要回到题干给出的具体代码、接口名和标准语义，避免用相似概念的经验结论替代本题要求。
