#pragma once
#include <string>
#include <array>
#include <memory>

class Trie {
public:
    Trie() = default;
    void insert(const std::string& word) {
        (void)word;
        // TODO: implement
    }
    bool search(const std::string& word) const {
        (void)word;
        // TODO: implement
        return false;
    }
    bool starts_with(const std::string& prefix) const {
        (void)prefix;
        // TODO: implement
        return false;
    }
private:
    struct Node {
        std::array<std::unique_ptr<Node>, 26> kids;
        bool end = false;
    };
    Node root_;
};
