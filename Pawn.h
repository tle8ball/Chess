#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"
#include "Board.h"

class Pawn : public Piece {
public:
    Pawn(const std::string& color, const Position& position);

    // Override pure virtual methods
    bool isValidMove(const Position& newPos, const Board& board) const override;
    char getSymbol() const override;

private:
    bool hasMoved_; // To check if the pawn has moved (for initial two-square advance)
};

#endif // PAWN_H
