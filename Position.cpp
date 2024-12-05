#include "Position.h"

// Default Constructor
Position::Position() : x_(0), y_(0) {}

// Parameterized Constructor
Position::Position(int x, int y) : x_(x), y_(y) {}

// Getters
int Position::getX() const {
    return x_;
}

int Position::getY() const {
    return y_;
}

// Setters
void Position::setX(int x) {
    x_ = x;
}

void Position::setY(int y) {
    y_ = y;
}

// Operator Overloads
bool Position::operator==(const Position& other) const {
    return x_ == other.x_ && y_ == other.y_;
}

bool Position::operator!=(const Position& other) const {
    return !(*this == other);
}
