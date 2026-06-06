#pragma once
#include <memory>
#include <string>
#include <sstream>

class Shape {
public:
    virtual ~Shape() = default;
    virtual std::string draw() const = 0;
};

class Circle : public Shape {
    double r_;
public:
    explicit Circle(double r) : r_(r) {}
    std::string draw() const override {
        std::ostringstream os;
        os << "Circle radius=" << r_;
        return os.str();
    }
};

class Square : public Shape {
    double s_;
public:
    explicit Square(double s) : s_(s) {}
    std::string draw() const override {
        std::ostringstream os;
        os << "Square side=" << s_;
        return os.str();
    }
};

class ShapeFactory {
public:
    static std::unique_ptr<Shape> create(const std::string& type, double param) {
        if (type == "circle") return std::make_unique<Circle>(param);
        if (type == "square") return std::make_unique<Square>(param);
        return nullptr;
    }
};
