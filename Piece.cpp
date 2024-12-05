#include "Piece.h"

// Constructor
Piece::Piece(const std::string& color, const Position& position)
    : color_(color), position_(position) {}

// Getters
std::string Piece::getColor() const {
    return color_;
}

Position Piece::getPosition() const {
    return position_;
}

// Setter
void Piece::setPosition(const Position& position) {
    position_ = position;
}
