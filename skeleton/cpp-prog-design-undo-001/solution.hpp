#pragma once
#include <string>
#include <stack>
#include <memory>

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class UndoRedoEditor {
    std::string text_;
    std::stack<std::unique_ptr<Command>> undo_stack_;
    std::stack<std::unique_ptr<Command>> redo_stack_;
public:
    void insert(char c, std::size_t pos) {
        struct InsertCmd : Command {
            std::string* t; char ch; std::size_t p;
            InsertCmd(std::string* t_, char c_, std::size_t pos_)
                : t(t_), ch(c_), p(pos_) {}
            void execute() override { t->insert(p, 1, ch); }
            void undo() override { t->erase(p, 1); }
        };
        auto cmd = std::make_unique<InsertCmd>(&text_, c, pos);
        cmd->execute();
        undo_stack_.push(std::move(cmd));
        while (!redo_stack_.empty()) redo_stack_.pop();
    }
    void erase(std::size_t pos) {
        struct EraseCmd : Command {
            std::string* t; std::size_t p; char saved;
            EraseCmd(std::string* t_, std::size_t pos_)
                : t(t_), p(pos_), saved((*t_)[pos_]) {}
            void execute() override {
                saved = (*t)[p];
                t->erase(p, 1);
            }
            void undo() override { t->insert(p, 1, saved); }
        };
        auto cmd = std::make_unique<EraseCmd>(&text_, pos);
        cmd->execute();
        undo_stack_.push(std::move(cmd));
        while (!redo_stack_.empty()) redo_stack_.pop();
    }
    void undo() {
        if (undo_stack_.empty()) return;
        auto cmd = std::move(undo_stack_.top());
        undo_stack_.pop();
        cmd->undo();
        redo_stack_.push(std::move(cmd));
    }
    void redo() {
        if (redo_stack_.empty()) return;
        auto cmd = std::move(redo_stack_.top());
        redo_stack_.pop();
        cmd->execute();
        undo_stack_.push(std::move(cmd));
    }
    std::string text() const { return text_; }
};
