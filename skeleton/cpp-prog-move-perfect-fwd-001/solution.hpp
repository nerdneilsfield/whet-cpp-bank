#pragma once
#include <utility>

template <typename Func, typename... Args>
decltype(auto) wrapper(Func&& f, Args&&... args) {
    return std::forward<Func>(f)(std::forward<Args>(args)...);
}
