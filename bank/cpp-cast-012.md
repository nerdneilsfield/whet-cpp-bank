---
qid: cpp-cast-012
type: fill
kp: [cpp-casting]
difficulty: easy
answer_key: "未定义行为（修改实际为 const 的对象）"
---

# const_cast 修改原 const 变量

```cpp
const int ci = 10;
int* p = const_cast<int*>(&ci);
*p = 20;  // 此行
std::cout << ci;
```

执行 "此行" 属于什么行为？___

## Explanation

答案是 `未定义行为（修改实际为 const 的对象）`。题干要求填写的是能直接满足语法、命令或代码执行结果的精确文本，其他近似写法通常会改变含义或无法通过严格匹配。常见误区是把相关概念写成解释性短语，或忽略空格、符号、大小写等细节。类型转换题要区分编译期转换、运行期检查、cv 限定和底层位模式重解释。
