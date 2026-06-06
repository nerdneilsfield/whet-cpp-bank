#pragma once
#include <unordered_map>
#include <list>
#include <cstddef>
#include <cassert>

class LFUCache {
    int cap_;
    struct Node { int key, val, freq; };
    std::unordered_map<int, std::list<Node>::iterator> map_;
    std::unordered_map<int, std::list<Node>> freq_map_;
    int min_freq_ = 0;
public:
    explicit LFUCache(int cap) : cap_(cap) {}
    int get(int key) {
        auto it = map_.find(key);
        if (it == map_.end()) return -1;
        auto node = *it->second;  // copy before erase
        int old_freq = node.freq;
        int new_freq = old_freq + 1;
        freq_map_[old_freq].erase(it->second);
        if (freq_map_[old_freq].empty()) {
            freq_map_.erase(old_freq);
            if (min_freq_ == old_freq) ++min_freq_;
        }
        node.freq = new_freq;
        freq_map_[new_freq].push_front(std::move(node));
        map_[key] = freq_map_[new_freq].begin();
        return map_[key]->val;
    }
    void put(int key, int val) {
        if (cap_ <= 0) return;
        auto it = map_.find(key);
        if (it != map_.end()) {
            it->second->val = val;
            get(key);
            return;
        }
        if ((int)map_.size() >= cap_) {
            auto& min_list = freq_map_[min_freq_];
            int evict_key = min_list.back().key;
            map_.erase(evict_key);
            min_list.pop_back();
            if (min_list.empty()) freq_map_.erase(min_freq_);
        }
        min_freq_ = 1;
        Node n{key, val, 1};
        freq_map_[1].push_front(n);
        map_[key] = freq_map_[1].begin();
    }
};
