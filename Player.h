#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Board.h"
#include "Move.h"
#include "InputHandler.h"

class Player {
public:
    // Constructor
    Player(const std::string& name, const std::string& color);

    // Destructor
    virtual ~Player() = default;

    // Getters
    std::string getName() const;
    std::string getColor() const;

    // Make a move
    std::unique_ptr<Move> makeMove(Board& board, InputHandler& inputHandler);

protected:
    std::string name_;
    std::string color_; // "white" or "black"
};

#endif // PLAYER_H
