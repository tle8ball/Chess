#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"
#include "InputHandler.h"
#include "Display.h"
#include "Move.h"
#include <vector>
#include <memory>

class Game {
public:
    // Constructor
    Game();

    // Start the game
    void start();

private:
    Board board_;
    Player player1_;
    Player player2_;
    InputHandler inputHandler_;
    Player* currentPlayer_;
    Display display_;

    // Move history
    std::vector<std::unique_ptr<Move>> moveHistory_;

    // Switch the current player
    void switchTurn();

    // Check if the current player is in check
    bool isInCheck(const std::string& color);

    // Check if the current player is in checkmate
    bool isCheckmate(const std::string& color);

    // Check if the game is in stalemate
    bool isStalemate(const std::string& color);

    // Get the king's position for a given color
    Position findKingPosition(const std::string& color);

    // Determine if any valid moves are available for a player
    bool hasValidMoves(const std::string& color);
};

#endif // GAME_H
