#include "Game.h"
#include <iostream>

Game::Game()
    : player1_("Player 1", "white"),
      player2_("Player 2", "black"),
      currentPlayer_(&player1_) {}

void Game::start() {
    while (true) {
        // Display the board at the start of each turn
        display_.render(board_);

        // Check for checkmate or stalemate
        if (isCheckmate(currentPlayer_->getColor())) {
            std::cout << "Checkmate! " << (currentPlayer_->getColor() == "white" ? "Black" : "White")
                      << " wins!" << std::endl;
            break;
        } else if (isStalemate(currentPlayer_->getColor())) {
            std::cout << "Stalemate! It's a draw!" << std::endl;
            break;
        } else if (isInCheck(currentPlayer_->getColor())) {
            std::cout << currentPlayer_->getName() << " is in check!" << std::endl;
        }

        // Current player makes a move
        std::unique_ptr<Move> move = currentPlayer_->makeMove(board_, inputHandler_);
        if (move) {
            // Execute the move
            move->execute(board_);
            moveHistory_.push_back(std::move(move));

            // After the move, check if the current player's king is still in check
            if (isInCheck(currentPlayer_->getColor())) {
                // Undo the move
                std::cout << "You cannot make a move that leaves your king in check." << std::endl;
                moveHistory_.back()->undo(board_);
                moveHistory_.pop_back();
                continue;
            }

            // **Display the updated board after the move**
            board_.displayBoard();

            // Switch turns
            switchTurn();
        } else {
            std::cout << "Move failed. Try again." << std::endl;
        }
    }
}


void Game::switchTurn() {
    if (currentPlayer_ == &player1_) {
        currentPlayer_ = &player2_;
    } else {
        currentPlayer_ = &player1_;
    }
}

bool Game::isInCheck(const std::string& color) {
    Position kingPos = findKingPosition(color);
    std::string opponentColor = (color == "white") ? "black" : "white";

    // Iterate over all opponent's pieces to see if any can capture the king
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            Piece* piece = board_.getPieceAt(Position(x, y));
            if (piece != nullptr && piece->getColor() == opponentColor) {
                if (piece->isValidMove(kingPos, board_)) {
                    // For non-knight pieces, check if the path is clear
                    if (dynamic_cast<Knight*>(piece) != nullptr || board_.isPathClear(piece->getPosition(), kingPos)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Game::isCheckmate(const std::string& color) {
    if (!isInCheck(color)) {
        return false;
    }

    if (!hasValidMoves(color)) {
        return true;
    }

    return false;
}

bool Game::isStalemate(const std::string& color) {
    if (isInCheck(color)) {
        return false;
    }

    if (!hasValidMoves(color)) {
        return true;
    }

    return false;
}

Position Game::findKingPosition(const std::string& color) {
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            Piece* piece = board_.getPieceAt(Position(x, y));
            if (piece != nullptr && piece->getColor() == color) {
                if (dynamic_cast<King*>(piece) != nullptr) {
                    return Position(x, y);
                }
            }
        }
    }
    // Should not reach here; the king must be on the board
    return Position(-1, -1);
}

bool Game::hasValidMoves(const std::string& color) {
    // Iterate over all pieces of the given color
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            Piece* piece = board_.getPieceAt(Position(x, y));
            if (piece != nullptr && piece->getColor() == color) {
                // Try all possible moves for this piece
                for (int newY = 0; newY < 8; ++newY) {
                    for (int newX = 0; newX < 8; ++newX) {
                        Position from(x, y);
                        Position to(newX, newY);

                        // Skip if moving to the same position
                        if (from == to) {
                            continue;
                        }

                        // Check if the move is valid
                        if (piece->isValidMove(to, board_)) {
                            // Check if the path is clear (except for Knight)
                            if (dynamic_cast<Knight*>(piece) == nullptr && !board_.isPathClear(from, to)) {
                                continue;
                            }

                            // Check if moving to a square occupied by own piece
                            Piece* targetPiece = board_.getPieceAt(to);
                            if (targetPiece != nullptr && targetPiece->getColor() == color) {
                                continue;
                            }

                            // Make the move temporarily
                            Piece* capturedPiece = targetPiece;
                            Move testMove(from, to, piece, capturedPiece);
                            testMove.execute(board_);

                            // Check if the player is still in check
                            bool inCheck = isInCheck(color);

                            // Undo the move
                            testMove.undo(board_);

                            // If the move results in no check, it's a valid move
                            if (!inCheck) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    // No valid moves found
    return false;
}
