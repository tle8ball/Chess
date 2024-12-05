#include "King.h"
#include <cmath>

King::King(const std::string& color, const Position& position)
    : Piece(color, position), hasMoved_(false) {}

bool King::isValidMove(const Position& newPos, const Board& board) const {
    int dx = std::abs(newPos.getX() - position_.getX());
    int dy = std::abs(newPos.getY() - position_.getY());

    // King moves one square in any direction
    if ((dx <= 1 && dy <= 1) && !(dx == 0 && dy == 0)) {
        auto destinationPiece = board.getPieceAt(newPos);
        if (destinationPiece == nullptr || destinationPiece->getColor() != color_) {
            return true;
        }
    }

    // Castling (not fully implemented, placeholder)
    // TODO: Implement castling logic

    return false;
}

char King::getSymbol() const {
    return (color_ == "white") ? 'K' : 'k';
}
