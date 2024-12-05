#include "Board.h"
#include <iostream>

// Constructor
Board::Board() {
    // Resize the outer vector to have 8 rows
    grid_.resize(8);

    // For each row, resize it to have 8 columns
    for (auto& row : grid_) {
        row.resize(8);
    }

    initializeBoard();
}

// Initialize the board with pieces in their starting positions
void Board::initializeBoard() {
    clearBoard();

    // Place black pieces
    grid_[0][0] = std::make_unique<Rook>("black", Position(0, 0));
    grid_[0][1] = std::make_unique<Knight>("black", Position(1, 0));
    grid_[0][2] = std::make_unique<Bishop>("black", Position(2, 0));
    grid_[0][3] = std::make_unique<Queen>("black", Position(3, 0));
    grid_[0][4] = std::make_unique<King>("black", Position(4, 0));
    grid_[0][5] = std::make_unique<Bishop>("black", Position(5, 0));
    grid_[0][6] = std::make_unique<Knight>("black", Position(6, 0));
    grid_[0][7] = std::make_unique<Rook>("black", Position(7, 0));

    for (int i = 0; i < 8; ++i) {
        grid_[1][i] = std::make_unique<Pawn>("black", Position(i, 1));
    }

    // Place white pieces
    grid_[7][0] = std::make_unique<Rook>("white", Position(0, 7));
    grid_[7][1] = std::make_unique<Knight>("white", Position(1, 7));
    grid_[7][2] = std::make_unique<Bishop>("white", Position(2, 7));
    grid_[7][3] = std::make_unique<Queen>("white", Position(3, 7));
    grid_[7][4] = std::make_unique<King>("white", Position(4, 7));
    grid_[7][5] = std::make_unique<Bishop>("white", Position(5, 7));
    grid_[7][6] = std::make_unique<Knight>("white", Position(6, 7));
    grid_[7][7] = std::make_unique<Rook>("white", Position(7, 7));

    for (int i = 0; i < 8; ++i) {
        grid_[6][i] = std::make_unique<Pawn>("white", Position(i, 6));
    }
}

// Move a piece from one position to another
bool Board::movePiece(const Position& from, const Position& to) {
    if (!isPositionValid(from) || !isPositionValid(to)) {
        std::cout << "Invalid position!" << std::endl;
        return false;
    }

    Piece* movingPiece = getPieceAt(from);
    if (movingPiece == nullptr) {
        std::cout << "No piece at the source position!" << std::endl;
        return false;
    }

    if (!movingPiece->isValidMove(to, *this)) {
        std::cout << "Invalid move for the piece!" << std::endl;
        return false;
    }

    // Check if the path is clear for pieces that cannot jump
    if (dynamic_cast<Knight*>(movingPiece) == nullptr) {
        if (!isPathClear(from, to)) {
            std::cout << "Path is not clear!" << std::endl;
            return false;
        }
    }

    Piece* destinationPiece = getPieceAt(to);
    if (destinationPiece != nullptr && destinationPiece->getColor() == movingPiece->getColor()) {
        std::cout << "Cannot capture your own piece!" << std::endl;
        return false;
    }

    // Move the piece
    movingPiece->setPosition(to);
    grid_[to.getY()][to.getX()] = std::move(grid_[from.getY()][from.getX()]);
    grid_[from.getY()][from.getX()] = nullptr;

    // If there was a piece at the destination, it is automatically deleted due to unique_ptr

    return true;
}

// Get the piece at a specific position
Piece* Board::getPieceAt(const Position& position) const {
    if (!isPositionValid(position)) {
        return nullptr;
    }
    return grid_[position.getY()][position.getX()].get();
}

// Display the board (for text-based interface)
void Board::displayBoard() const {
    std::cout << "  +------------------------+" << std::endl;
    for (int y = 0; y < 8; ++y) {
        std::cout << 8 - y << " | ";
        for (int x = 0; x < 8; ++x) {
            Piece* piece = grid_[y][x].get();
            if (piece) {
                std::cout << piece->getSymbol() << " ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "  +------------------------+" << std::endl;
    std::cout << "    a b c d e f g h" << std::endl;
}

// Check if a position is within the bounds of the board
bool Board::isPositionValid(const Position& position) const {
    int x = position.getX();
    int y = position.getY();
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}

// Check if the path between two positions is clear
bool Board::isPathClear(const Position& from, const Position& to) const {
    int dx = to.getX() - from.getX();
    int dy = to.getY() - from.getY();

    int stepX = (dx == 0) ? 0 : (dx > 0 ? 1 : -1);
    int stepY = (dy == 0) ? 0 : (dy > 0 ? 1 : -1);

    int x = from.getX() + stepX;
    int y = from.getY() + stepY;

    while (x != to.getX() || y != to.getY()) {
        if (grid_[y][x] != nullptr) {
            return false;
        }
        x += stepX;
        y += stepY;
    }

    return true;
}

// Helper method to clear the board
void Board::clearBoard() {
    for (auto& row : grid_) {
        for (auto& cell : row) {
            cell.reset();
        }
    }
}

// Move a piece from one position to another without validation
void Board::movePieceOnBoard(const Position& from, const Position& to) {
    if (!isPositionValid(from) || !isPositionValid(to)) {
        return;
    }

    grid_[to.getY()][to.getX()] = std::move(grid_[from.getY()][from.getX()]);
    grid_[from.getY()][from.getX()] = nullptr;
}

// Remove a piece at a specific position
void Board::removePieceAt(const Position& position) {
    if (!isPositionValid(position)) {
        return;
    }

    grid_[position.getY()][position.getX()].reset();
}

// Place a piece at a specific position
void Board::placePieceAt(const Position& position, Piece* piece) {
    if (!isPositionValid(position) || piece == nullptr) {
        return;
    }

    // Transfer ownership of the piece to the board
    grid_[position.getY()][position.getX()] = std::unique_ptr<Piece>(piece);
}