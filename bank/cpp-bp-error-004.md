---
qid: cpp-bp-error-004
type: single
kp: [cpp-exceptions]
difficulty: medium
answer_key: B
---

下面的"防御性"代码评审，哪点是**反模式**？

```cpp
Result process_order(const Order& o) {
    try {
        validate(o);          // 可能抛 InvalidOrder
        auto p = compute_price(o);
        charge(o.user_id, p); // 可能抛 PaymentError
        ship(o);              // 可能抛 ShippingError
        return Result::ok();
    } catch (...) {
        return Result::fail("unknown error");
    }
}
```

A. 应捕获具体异常类型而非 `...`
B. 不应在此层 `catch(...)` 后转字符串吞掉信息，应让异常传播给真正能恢复的调用者
C. 应在每行加 try-catch 以便定位
D. 应在函数前加 `noexcept` 提升性能

---

## 解析

`catch(...)` 后返回"unknown error"是把**结构化异常信息（类型、消息、堆栈）压扁成单一字符串**的反模式，俗称 "exception swallowing"。后果：
- 排查问题时丢失关键信息（哪种异常？在哪一步？）
- 上层得不到精准的错误类型，无法做差异化恢复（如 PaymentError 该重试，ShippingError 该回滚）
- 测试时一切"正常"，生产环境出 bug 难以追溯

正确原则：**只在能真正处理（recover/transform）该异常的层 catch**。中间层应允许异常向上传播。

C 在每行加 try-catch 是另一种过度防御，使代码不可读。D 加 noexcept 会让任何异常直接 terminate，更糟。

正确做法：
```cpp
Result process_order(const Order& o) {
    try {
        validate(o);
        charge(o.user_id, compute_price(o));
        ship(o);
        return Result::ok();
    } catch (const PaymentError& e) {
        return Result::retry(e.what());     // 可恢复
    } catch (const InvalidOrder& e) {
        return Result::reject(e.what());    // 用户错误
    }
    // ShippingError 等未知严重错误：让它传播
}
```