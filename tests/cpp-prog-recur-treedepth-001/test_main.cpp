#include "../skeleton/solution.hpp"
#include <cassert>
static void freeTree(Node* n){ if(!n) return; freeTree(n->left); freeTree(n->right); delete n; }
int main(){
    assert(maxDepth(nullptr) == 0);
    {
        Node* r = new Node(1);
        assert(maxDepth(r) == 1);
        freeTree(r);
    }
    {
        Node* r = new Node(1);
        r->left = new Node(2);
        r->right = new Node(3);
        r->left->left = new Node(4);
        assert(maxDepth(r) == 3);
        freeTree(r);
    }
    {
        Node* r = new Node(1);
        r->right = new Node(2);
        r->right->right = new Node(3);
        r->right->right->right = new Node(4);
        assert(maxDepth(r) == 4);
        freeTree(r);
    }
    {
        Node* r = new Node(1);
        r->left = new Node(2);
        r->left->left = new Node(3);
        r->right = new Node(4);
        assert(maxDepth(r) == 3);
        freeTree(r);
    }
    return 0;
}
