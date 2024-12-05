#include "Move.h"
#include "Board.h"
#include <utility>

// Constructor
Move::Move(const Position& from, const Position& to, Piece* pieceMoved, Piece* pieceCaptured)
    : from_(from), to_(to), pieceMoved_(pieceMoved), pieceCaptured_(pieceCaptured) {}

// Execute the move on the board
void Move::execute(Board& board) {
    // Remove the captured piece from the board (if any)
    if (pieceCaptured_) {
        board.removePieceAt(to_);
    }

    // Move the piece on the board
    board.movePieceOnBoard(from_, to_);

    // Update the piece's position
    pieceMoved_->setPosition(to_);
}

// Undo the move on the board
void Move::undo(Board& board) {
    // Move the piece back to its original position
    board.movePieceOnBoard(to_, from_);

    // Restore the piece's position
    pieceMoved_->setPosition(from_);

    // Restore the captured piece (if any)
    if (pieceCaptured_) {
        board.placePieceAt(to_, pieceCaptured_);
    }
}

// Getters
Position Move::getFrom() const {
    return from_;
}

Position Move::getTo() const {
    return to_;
}

Piece* Move::getPieceMoved() const {
    return pieceMoved_;
}

Piece* Move::getPieceCaptured() const {
    return pieceCaptured_;
}
