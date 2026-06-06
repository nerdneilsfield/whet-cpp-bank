#pragma once
#include <memory>
#include <utility>

template <typename>
class Function;

template <typename R, typename... Args>
class Function<R(Args...)> {
    struct CallableBase {
        virtual ~CallableBase() = default;
        virtual CallableBase* clone() const = 0;
        virtual R invoke(Args... args) = 0;
    };
    template <typename F>
    struct Callable : CallableBase {
        F f;
        Callable(F f_) : f(std::move(f_)) {}
        CallableBase* clone() const override { return new Callable(f); }
        R invoke(Args... args) override { return f(std::forward<Args>(args)...); }
    };
    std::unique_ptr<CallableBase> ptr_;
public:
    Function() = default;
    template <typename F>
    Function(F f) : ptr_(std::make_unique<Callable<F>>(std::move(f))) {}
    Function(const Function& o) : ptr_(o.ptr_ ? o.ptr_->clone() : nullptr) {}
    Function(Function&& o) noexcept = default;
    Function& operator=(const Function& o) {
        ptr_.reset(o.ptr_ ? o.ptr_->clone() : nullptr);
        return *this;
    }
    Function& operator=(Function&& o) noexcept = default;
    explicit operator bool() const noexcept { return !!ptr_; }
    R operator()(Args... args) const {
        return const_cast<Function*>(this)->ptr_->invoke(std::forward<Args>(args)...);
    }
};
