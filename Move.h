#ifndef MOVE_H
#define MOVE_H

#include "Position.h"
#include "Piece.h"
#include <memory>

class Move {
public:
    // Constructor
    Move(const Position& from, const Position& to, Piece* pieceMoved, Piece* pieceCaptured = nullptr);

    // Execute the move on the board
    void execute(Board& board);

    // Undo the move on the board
    void undo(Board& board);

    // Getters
    Position getFrom() const;
    Position getTo() const;
    Piece* getPieceMoved() const;
    Piece* getPieceCaptured() const;

private:
    Position from_;
    Position to_;
    Piece* pieceMoved_;
    Piece* pieceCaptured_;
};

#endif // MOVE_H
