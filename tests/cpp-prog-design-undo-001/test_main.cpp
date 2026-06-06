#include "../skeleton/solution.hpp"
#include <cassert>
int main() {
    {
        UndoRedoEditor ed;
        assert(ed.text() == "");
    }
    {
        UndoRedoEditor ed;
        ed.insert('a', 0);
        ed.insert('b', 1);
        ed.insert('c', 2);
        assert(ed.text() == "abc");
    }
    {
        UndoRedoEditor ed;
        ed.insert('a', 0);
        ed.insert('b', 1);
        ed.erase(1);
        assert(ed.text() == "a");
    }
    {
        UndoRedoEditor ed;
        ed.insert('x', 0);
        ed.insert('y', 1);
        ed.undo();
        assert(ed.text() == "x");
        ed.undo();
        assert(ed.text() == "");
        ed.redo();
        assert(ed.text() == "x");
        ed.redo();
        assert(ed.text() == "xy");
    }
    {
        UndoRedoEditor ed;
        ed.insert('a', 0);
        ed.undo();
        ed.insert('b', 0);
        assert(ed.text() == "b");
        ed.redo();
        assert(ed.text() == "b");
    }
    return 0;
}
