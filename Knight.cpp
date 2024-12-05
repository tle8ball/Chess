#include "Knight.h"
#include <cmath>

Knight::Knight(const std::string& color, const Position& position)
    : Piece(color, position) {}

bool Knight::isValidMove(const Position& newPos, const Board& board) const {
    int dx = std::abs(newPos.getX() - position_.getX());
    int dy = std::abs(newPos.getY() - position_.getY());

    // Knight moves in an L-shape: 2 by 1 or 1 by 2
    if ((dx == 2 && dy == 1) || (dx == 1 && dy == 2)) {
        auto destinationPiece = board.getPieceAt(newPos);
        if (destinationPiece == nullptr || destinationPiece->getColor() != color_) {
            return true;
        }
    }

    return false;
}

char Knight::getSymbol() const {
    return (color_ == "white") ? 'N' : 'n';
}
