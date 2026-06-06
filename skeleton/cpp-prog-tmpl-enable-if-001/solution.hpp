#pragma once
#include <type_traits>

template <typename T>
typename std::enable_if<std::is_integral<T>::value, T>::type
process(T val) {
    return val * 2;
}

template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, double>::type
process(T val) {
    return val / 2.0;
}
