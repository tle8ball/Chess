#include "Bishop.h"
#include <cmath>

Bishop::Bishop(const std::string& color, const Position& position)
    : Piece(color, position) {}

bool Bishop::isValidMove(const Position& newPos, const Board& board) const {
    int dx = newPos.getX() - position_.getX();
    int dy = newPos.getY() - position_.getY();

    // Move is along a diagonal
    if (std::abs(dx) == std::abs(dy)) {
        int stepX = (dx > 0) ? 1 : -1;
        int stepY = (dy > 0) ? 1 : -1;

        int x = position_.getX() + stepX;
        int y = position_.getY() + stepY;

        // Check for obstructions
        while (x != newPos.getX() && y != newPos.getY()) {
            if (board.getPieceAt(Position(x, y)) != nullptr) {
                return false;
            }
            x += stepX;
            y += stepY;
        }

        // Check if destination has a piece of the same color
        auto destinationPiece = board.getPieceAt(newPos);
        if (destinationPiece == nullptr || destinationPiece->getColor() != color_) {
            return true;
        }
    }

    return false;
}

char Bishop::getSymbol() const {
    return (color_ == "white") ? 'B' : 'b';
}
