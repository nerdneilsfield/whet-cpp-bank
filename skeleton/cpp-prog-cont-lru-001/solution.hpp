#pragma once
#include <list>
#include <unordered_map>

class LRUCache {
public:
    explicit LRUCache(int capacity) : cap_(capacity) {}
    int get(int key) {
        (void)key;
        // TODO: implement
        return -1;
    }
    void put(int key, int value) {
        (void)key; (void)value;
        // TODO: implement
    }
private:
    int cap_;
    std::list<std::pair<int,int>> lst_;
    std::unordered_map<int, std::list<std::pair<int,int>>::iterator> map_;
};
