#include "Pawn.h"
#include <cmath>

Pawn::Pawn(const std::string& color, const Position& position)
    : Piece(color, position), hasMoved_(false) {}

bool Pawn::isValidMove(const Position& newPos, const Board& board) const {
    int direction = (color_ == "white") ? -1 : 1;
    int startRow = (color_ == "white") ? 6 : 1;

    int dx = newPos.getX() - position_.getX();
    int dy = newPos.getY() - position_.getY();

    // Forward move
    if (dx == 0) {
        // Single square advance
        if (dy == direction) {
            return board.getPieceAt(newPos) == nullptr;
        }
        // Double square advance from starting position
        else if (dy == 2 * direction && position_.getY() == startRow) {
            Position intermediatePos(position_.getX(), position_.getY() + direction);
            return board.getPieceAt(newPos) == nullptr &&
                   board.getPieceAt(intermediatePos) == nullptr;
        }
    }
    // Diagonal capture
    else if (std::abs(dx) == 1 && dy == direction) {
        auto targetPiece = board.getPieceAt(newPos);
        if (targetPiece != nullptr && targetPiece->getColor() != color_) {
            return true;
        }
    }

    return false;
}

char Pawn::getSymbol() const {
    return (color_ == "white") ? 'P' : 'p';
}
