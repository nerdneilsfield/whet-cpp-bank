#pragma once
#include <functional>
#include <utility>

template <typename Func>
auto curry(Func&& f) {
    return [f = std::forward<Func>(f)](auto a) {
        return [f, a](auto b) {
            return [f, a, b](auto c) {
                return f(a, b, c);
            };
        };
    };
}
