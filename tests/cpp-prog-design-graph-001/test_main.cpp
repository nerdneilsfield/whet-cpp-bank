#include "../skeleton/solution.hpp"
#include <cassert>
int main() {
    {
        Graph g;
        assert(g.vertex_count() == 0);
        g.add_edge(1, 2);
        assert(g.vertex_count() >= 2);
        assert(g.has_edge(1, 2));
        assert(!g.has_edge(2, 1));
    }
    {
        Graph g;
        g.add_edge(1, 2); g.add_edge(2, 3);
        assert(g.has_path(1, 3));
        assert(!g.has_path(3, 1));
    }
    {
        Graph g;
        g.add_edge(1, 2); g.add_edge(2, 4);
        g.add_edge(1, 3); g.add_edge(3, 4);
        assert(g.has_path(1, 4));
        assert(!g.has_path(4, 1));
    }
    {
        Graph g;
        assert(!g.has_path(1, 2));
    }
    {
        Graph g;
        g.add_edge(1, 1);
        assert(g.has_path(1, 1));
    }
    {
        Graph g;
        g.add_edge(1, 2); g.add_edge(3, 4);
        assert(!g.has_path(1, 4));
        g.add_edge(2, 3);
        assert(g.has_path(1, 4));
    }
    return 0;
}
