#pragma once
#include <unordered_map>
#include <typeindex>
#include <functional>
#include <memory>
#include <vector>

class EventBus {
    std::unordered_map<std::type_index, std::vector<void*>> subs_;
public:
    template <typename T>
    void subscribe(std::function<void(T)> cb) {
        auto& vec = subs_[std::type_index(typeid(T))];
        vec.push_back(new std::function<void(T)>(std::move(cb)));
    }
    template <typename T>
    void publish(const T& event) {
        auto it = subs_.find(std::type_index(typeid(T)));
        if (it == subs_.end()) return;
        for (auto* p : it->second) {
            auto* cb = static_cast<std::function<void(T)>*>(p);
            (*cb)(event);
        }
    }
};
