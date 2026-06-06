#pragma once
#include <vector>
#include <memory>

class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
};

class Circle : public Shape {
public:
    explicit Circle(double r) : r_(r) {}
    double area() const override {
        // TODO: implement
        return 0.0;
    }
private:
    double r_;
};

class Rectangle : public Shape {
public:
    Rectangle(double w, double h) : w_(w), h_(h) {}
    double area() const override {
        // TODO: implement
        return 0.0;
    }
private:
    double w_, h_;
};

inline double total_area(const std::vector<std::unique_ptr<Shape>>& shapes) {
    (void)shapes;
    // TODO: implement
    return 0.0;
}
