#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <string>
#include "Position.h"

class InputHandler {
public:
    // Constructor
    InputHandler() = default;

    // Destructor
    ~InputHandler() = default;

    // Get input from the player
    std::string getPlayerInput() const;

    // Parse the input into from and to positions
    bool parseInput(const std::string& input, Position& from, Position& to) const;

private:
    // Helper method to convert algebraic notation to Position
    bool notationToPosition(const std::string& notation, Position& position) const;
};

#endif // INPUTHANDLER_H
