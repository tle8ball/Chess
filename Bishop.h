#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"
#include "Board.h"

class Bishop : public Piece {
public:
    Bishop(const std::string& color, const Position& position);

    // Override pure virtual methods
    bool isValidMove(const Position& newPos, const Board& board) const override;
    char getSymbol() const override;
};

#endif // BISHOP_H
