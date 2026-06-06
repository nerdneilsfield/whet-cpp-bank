#pragma once

template <class T>
inline T vmin(T a) {
    return a;
}

template <class T, class... Rest>
inline T vmin(T a, Rest... rest) {
    (void)a;
    // TODO: implement
    return a;
}
