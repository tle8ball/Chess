#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"
#include "Board.h"

class Queen : public Piece {
public:
    Queen(const std::string& color, const Position& position);

    // Override pure virtual methods
    bool isValidMove(const Position& newPos, const Board& board) const override;
    char getSymbol() const override;
};

#endif // QUEEN_H
