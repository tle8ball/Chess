#ifndef KING_H
#define KING_H

#include "Piece.h"
#include "Board.h"

class King : public Piece {
public:
    King(const std::string& color, const Position& position);

    // Override pure virtual methods
    bool isValidMove(const Position& newPos, const Board& board) const override;
    char getSymbol() const override;

private:
    bool hasMoved_; // To check if the king has moved (for castling)
};

#endif // KING_H
