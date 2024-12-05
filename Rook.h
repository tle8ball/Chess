#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"
#include "Board.h"

class Rook : public Piece {
public:
    Rook(const std::string& color, const Position& position);

    // Override pure virtual methods
    bool isValidMove(const Position& newPos, const Board& board) const override;
    char getSymbol() const override;
};

#endif // ROOK_H
