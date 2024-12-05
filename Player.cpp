#include "Player.h"
#include <iostream>

Player::Player(const std::string& name, const std::string& color)
    : name_(name), color_(color) {}

std::string Player::getName() const {
    return name_;
}

std::string Player::getColor() const {
    return color_;
}

std::unique_ptr<Move> Player::makeMove(Board& board, InputHandler& inputHandler) {
    while (true) {
        // Prompt the player for input
        std::cout << name_ << " (" << color_ << "), enter your move (e.g., e2e4): ";
        std::string input = inputHandler.getPlayerInput();

        // Parse the input into positions
        Position from, to;
        if (!inputHandler.parseInput(input, from, to)) {
            std::cout << "Invalid input format. Please try again." << std::endl;
            continue;
        }

        // Get the piece at the source position
        Piece* pieceMoved = board.getPieceAt(from);
        if (pieceMoved == nullptr) {
            std::cout << "No piece at the source position." << std::endl;
            continue;
        }

        // Check if the piece belongs to the current player
        if (pieceMoved->getColor() != color_) {
            std::cout << "You can only move your own pieces." << std::endl;
            continue;
        }

        // Check if the move is valid for the piece
        if (!pieceMoved->isValidMove(to, board)) {
            std::cout << "Invalid move for the selected piece." << std::endl;
            continue;
        }

        // Check if the path is clear (except for Knight)
        if (dynamic_cast<Knight*>(pieceMoved) == nullptr) {
            if (!board.isPathClear(from, to)) {
                std::cout << "Path is not clear." << std::endl;
                continue;
            }
        }

        // Get any piece at the destination
        Piece* pieceCaptured = board.getPieceAt(to);

        // Check if the destination has a piece of the same color
        if (pieceCaptured != nullptr && pieceCaptured->getColor() == color_) {
            std::cout << "Cannot capture your own piece." << std::endl;
            continue;
        }

        // Create and return the Move object
        return std::make_unique<Move>(from, to, pieceMoved, pieceCaptured);
    }
}
