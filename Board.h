#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Position.h"

class Board {
public:
    // Constructor
    Board();

    // Destructor
    ~Board() = default;

    // Delete copy constructor and assignment operator
    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;

    // Board Initialization
    void initializeBoard();

    // Move a piece from one position to another
    bool movePiece(const Position& from, const Position& to);

    // Get the piece at a specific position
    Piece* getPieceAt(const Position& position) const;

    // Display the board (for text-based interface)
    void displayBoard() const;

    // Check if a position is within the bounds of the board
    bool isPositionValid(const Position& position) const;

    // Check if the path between two positions is clear (for linear moving pieces)
    bool isPathClear(const Position& from, const Position& to) const;

    // Move a piece from one position to another without validation (used internally)
    void movePieceOnBoard(const Position& from, const Position& to);

    // Remove a piece at a specific position
    void removePieceAt(const Position& position);

    // Place a piece at a specific position
    void placePieceAt(const Position& position, Piece* piece);


private:
    // 8x8 grid representing the chessboard
    std::vector<std::vector<std::unique_ptr<Piece>>> grid_;

    // Helper method to clear the board
    void clearBoard();
};

#endif // BOARD_H
