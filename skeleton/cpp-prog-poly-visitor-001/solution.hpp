#pragma once
#include <variant>
#include <string>

using Value = std::variant<int, double, std::string>;

inline std::string describe(const Value& v) {
    (void)v;
    // TODO: implement using std::visit
    return {};
}
