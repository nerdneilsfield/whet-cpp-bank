#pragma once
#include <algorithm>

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

inline int maxDepth(Node* root) {
    // TODO: implement
    (void)root;
    return 0;
}
