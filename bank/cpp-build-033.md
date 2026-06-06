---
qid: cpp-build-033
type: fill
kp: [cpp-build-tools]
difficulty: easy
answer_key: "target_link_libraries(app mylib)"
---

# 在 CMake 中，将库 `mylib` 链接到可执行目标 `app` 的命令是：

`____`

## Explanation

答案是 `target_link_libraries(app mylib)`。该命令把库目标或库名链接到目标 `app` 上，是现代 CMake 中表达目标依赖关系的核心命令。实际项目中还常配合 `PRIVATE`、`PUBLIC`、`INTERFACE` 指定依赖传播范围。
